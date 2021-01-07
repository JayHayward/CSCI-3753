/*
 * Jay Hayward
 * CSCI 3753
 * Programming Assignment 3
 *
 * File: queue.h
*/

#ifndef QUEUE_H
#define QUEUE_H

#define ENTRY_COUNT 20 // entries in the shared queue
// defined as 20 because that's what Abigail's sample code used
// can be changed to BUF_SIZE if necessary

void enq(char *name);
int deq(char **name);

#endif //QUEUE_H
