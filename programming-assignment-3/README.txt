/*
 * Jay Hayward
 * CSCI 3753
 * Programming Assignment 3
 *
 * File: README.txt
*/

To run my program, you must have :
  multi-lookup.h
  multi-lookup.c
  queue.c
  queue.h
  util.c
  util.h
  Makefile

you should also have any name files you want to test in a subdirectory called
`/inputs/`

run
`make clean`
to remove any leftover files, then run
`make`
to compile the program

the input you must use to run my program is given in the code, but to restate:
`./multi-lookup <# requester threads> <# resolver threads> serviced.txt results.txt ./inputs/*`
the results of the program will be printed to `results.txt` and
a summary of the performance will be printed to `performance.txt`
