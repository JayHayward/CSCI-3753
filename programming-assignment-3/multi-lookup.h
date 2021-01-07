/*
 * Jay Hayward
 * CSCI 3753
 * Programming Assignment 3
 *
 * File: multi-lookup.h
*/

#ifndef MULTI_LOOKUP_H
#define MULTI_LOOKUP_H


#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
// #include "util.h"

#define MAX_INPUT_FILES 10
#define INPUT_FILE_SIZE "%1024s"
#define MAX_RESOLVER_THREADS 10
#define MAX_REQUESTER_THREADS 5
#define MAX_NAME_LENGTH 1025
#define MAX_IP_LENGTH INET6_ADDRSTRLEN
#define BUF_SIZE 100  //temp value
#define ENTRY_COUNT 20
#define PERF_LOG "performance.txt"

#endif // MULTI_LOOKUP_H
