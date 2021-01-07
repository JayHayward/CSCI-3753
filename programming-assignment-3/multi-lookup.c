/*
 * Jay Hayward
 * CSCI 3753
 * Programming Assignment 3
 *
 * File: multi-lookup.c
*/



#include "multi-lookup.h"
#include "queue.h"
#include "util.h"


//// GLOBALS ////

int Argc; // copy of argc
char **Argv; // copy of argv
int lrv; // return value of dns lookup
int trv; // return value of creating a new thread
void *jrv; // return value of a join


int next_file; // next argv file to be processed
pthread_mutex_t mtx_inflile = PTHREAD_MUTEX_INITIALIZER; // for input file access
pthread_mutex_t mtx_serviced = PTHREAD_MUTEX_INITIALIZER; // for serviced.txt log
pthread_mutex_t mtx_results = PTHREAD_MUTEX_INITIALIZER; // for results.txt log

int total_lines_requested = 0;
int total_lines_resolved = 0;

// files
FILE *f_serviced, *f_results;  // request and response logs

int end_of_reqs = 0; // all requests have exited

// Requester and Resolver thread pools
pthread_t *req_thread;
pthread_t *res_thread;

int num_req_threads, num_res_threads; // number of requester and resolver threads defined in main


char *get_next_filename() {
  char *filename;

    pthread_mutex_lock(&mtx_inflile);
  if (next_file < Argc) { // if there are more files
    filename = Argv[next_file++]; // new filename
  }
    pthread_mutex_unlock(&mtx_inflile);

  return filename;
}


void *requester(void *param){ // you can initially pass NULL
  pthread_t self;
  int thread_id = *(int *)param; // pointer to a void* cast as an int*
  int files_serviced = 0;
  int retval; // will return the ID of invoked thread
  char *f_new; // new file stream
  FILE *f_stream;
  char line[MAX_NAME_LENGTH];

  self = pthread_self(); // returns id of the thread running

  while(next_file < Argc) { // while there are still more files in argv
    f_new = get_next_filename();

    if((f_stream = fopen(f_new, "r")) == NULL) {
      fprintf(stderr, "failed to read input file '%s'\n", f_new);
      continue; // keep looking for a valid file
    }
    files_serviced++;

    while(fscanf(f_stream, INPUT_FILE_SIZE, line) > 0) { // takes stuff from f_stream and puts it in line
      char *q_string = (char*) malloc(strlen(line) + 1); // +1 for null terminator
      strcpy(q_string, line); // q_string is string that gets added to shared buffer
      enq(q_string);
    }
    fclose(f_stream);
  }
    pthread_mutex_lock(&mtx_serviced); // mutex in case multiple threads want to write to file
  f_serviced = fopen("serviced.txt", "w+");
  if(f_serviced == NULL){
    fprintf(stderr, "cannot access serviced.txt\n");
    exit(1);
  }
  fprintf(f_serviced, "Thread %d serviced %d files\n", thread_id, files_serviced);
  fclose(f_serviced);
    pthread_mutex_unlock(&mtx_serviced);

  retval = (long int)self;
  pthread_exit((void *)(long int)retval);
}


void *resolver(void *param){
  pthread_t self;
  int thread_id = *(int *)param;
  int requests_processed = 0;
  int retval; // will return # requests processed with thread exit
  char *dns_name;
  char firstIPaddr[MAX_NAME_LENGTH];

  self = pthread_self();
  while(1){ //while there are more requests to process
    if(deq(&dns_name)) { // check if there are no more requests
      break;
    }
    requests_processed++;

    // query dns_lookup
    lrv = dnslookup(dns_name, firstIPaddr, MAX_NAME_LENGTH);

      pthread_mutex_lock(&mtx_results); // mutex in case multiple threads want to write to file
    f_results = fopen("results.txt", "a+");
    if(f_results == NULL) {
      fprintf(stderr,"cannot access results.txt\n");
      exit(1);
    }
    if(lrv != UTIL_SUCCESS) {
      fprintf(f_results, "%s,%s\n", dns_name, "");
      fprintf(stderr, "dns query failed");
    }
    else {
      fprintf(f_results, "%s,%s\n", dns_name, firstIPaddr);
    }
    // fprintf(f_results, "%s, %s\n", dns_name, ((lrv != UTIL_SUCCESS) ? "" : firstIPaddr));)
    printf("%s,%s\n", dns_name, ((lrv != UTIL_SUCCESS) ? "" : firstIPaddr)); //print to terminal
      pthread_mutex_unlock(&mtx_results);
    free(dns_name); // free memory malloc'd in requester()
  }
  retval = (long int)requests_processed;
  pthread_exit((void *)(long int)retval);
}


//// MAIN ////

int main(int argc, char *argv[]) {
  FILE *p_file; // performance report file
  Argc = argc;
  Argv = argv;
  next_file = 5; // files start at argv index 5


  //// Handle all usage  errors ////
  if(argc < 5) { // not enough files
    fprintf(stderr, "Invalid input. Usage: multi-lookup <# requester threads> <# resolver threads> serviced.txt results.txt [<data file 1> ... <data file N>]\n");
    exit(1);
  }

  // service file unspecified
  if((f_serviced = fopen(argv[3], "w")) == NULL) {
    fprintf(stderr, "Invalid: no serviced file specified\n");
    exit(1);
  }

  // results file unspecified
  if((f_results = fopen(argv[4], "w")) == NULL) {
    fprintf(stderr, "Invalid: no results file specified\n");
    exit(1);
  }

  // # requester threads is 0
  if((num_req_threads = atoi(argv[1])) < 1) {
    fprintf(stderr, "Invalid: Not enough requester threads specified");
    exit(1);
  }

  // # resolver threads is 0
  if((num_res_threads = atoi(argv[2])) < 1) {
    fprintf(stderr, "Invalid: Not enough resolver threads specified");
    exit(1);
  }

  struct timeval tv0, tv1; // start and end times
  // Get start time
  gettimeofday(&tv0, NULL);


  // Initialize threads
  req_thread = (pthread_t *)malloc(num_req_threads * sizeof(pthread_t));
  res_thread = (pthread_t *)malloc(num_res_threads * sizeof(pthread_t));


  // start Requester threads
  for(int i=0; i < num_req_threads; i++) {
    if(trv = pthread_create(&req_thread[i], NULL, requester, &i) != 0) {
      fprintf(stderr, "unable to create thread\n");
      exit(1);
    }
  }

  // Start Resolver threads
  for(int i=0; i < num_res_threads; i++) {
    if(trv = pthread_create(&res_thread[i], NULL, resolver, &i) != 0) {
      fprintf(stderr, "unable to create thread\n");
      exit(1);
    }
  }


  // Reap Requester threads
  for(int i=0; i < num_req_threads; i++) {
    trv = pthread_join(req_thread[i], &jrv);
  }
  end_of_reqs = 1; // all requests have exited

  // Reap Resolver threads
  for(int i=0; i < num_res_threads; i++) {
    trv = pthread_join(res_thread[i], &jrv);
  }

  // release all threads
  free(req_thread);
  free(res_thread);


  // Get end time
  gettimeofday(&tv1, NULL);
  long time_elapsed = (tv1.tv_sec - tv0.tv_sec)*1000000 + (tv1.tv_usec - tv0.tv_usec); // prints total seconds + microseconds
  printf("time elapsed is %ld microseconds\n", time_elapsed);


  // performance report
  if((p_file = fopen(PERF_LOG, "a+")) == NULL) {
    fprintf(stderr, "Failure to open performance file\n");
    exit(1);
  }


  // output format for performance log
  fprintf(p_file, "Number for requester thread = %d\nNumber for resolver thread = %d\nTime elapsed is %ld\n", num_req_threads, num_res_threads, time_elapsed);
  fclose(p_file);


  exit(0);
}
