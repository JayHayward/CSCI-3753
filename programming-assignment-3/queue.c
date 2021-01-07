/*
 * Jay Hayward
 * CSCI 3753
 * Programming Assignment 3
 *
 * File: queue.c
*/

#include "queue.h"

#include <pthread.h>
#include <string.h>
#include <stdio.h>

pthread_mutex_t mtx_q = PTHREAD_MUTEX_INITIALIZER; // Mutex for queue access
pthread_cond_t cond_q_empty = PTHREAD_COND_INITIALIZER;  // CondVar for queue empty
pthread_cond_t cond_q_full  = PTHREAD_COND_INITIALIZER;  // CondVar for queue full

char *q[ENTRY_COUNT]; //shared queue
int add_pos = 0; //position to add
int rem_pos = 0; //position to remove
int q_count = 0; //number of elements in buffer


int end_of_reqs;// Flag: all request threads have exit()ed.

// TODO //
// check ENTRY_COUNT. Could be BUF_SIZE?


// copy name to queue tail
void enq(char *name) {
  pthread_mutex_lock(&mtx_q);
    while (q_count >= ENTRY_COUNT) { //  check for free space
      pthread_cond_wait(&cond_q_full, &mtx_q);
    }

  // now there's free space
	q_count++;
	add_pos++; // move the tail pointer
	if (add_pos >= ENTRY_COUNT)	// wrap circular queue
		add_pos = 0;

	q[add_pos] = name;
    pthread_mutex_unlock(&mtx_q);
	pthread_cond_signal(&cond_q_empty);	// queue has stuff
}


int deq(char **name) {
// Returns 1 if queue is empty and requester threads are done
    pthread_mutex_lock(&mtx_q);
    while (q_count <= 0) { // check if queue has elements in it
		    if (end_of_reqs) { // no more requester threads coming
          pthread_mutex_unlock(&mtx_q);
          return 1;
        }
		pthread_cond_wait(&cond_q_empty, &mtx_q);
  }

	// Now there is More Stuff
	q_count--;
	rem_pos++; // move the head pointer
	if (rem_pos >= ENTRY_COUNT)	// wrap circular queue
	 rem_pos = 0;

	*name = q[rem_pos];
      pthread_mutex_unlock(&mtx_q);
	pthread_cond_signal(&cond_q_full);	// Queue has free space, call more threads

	return 0;	// Success
}
