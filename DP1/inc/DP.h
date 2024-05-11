/*
* FILE        DP.h
* PROJECT     Assignment 5
* PROGRAMMER  Beunard Lecaj, Jason Schneider
* DESCRIPTION  This file contains all the includes, constants and structs used by the histo-system
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/sem.h>
#include <time.h>


/* ======================================================= */
/*                      CONSTANTS                          */
/* ======================================================= */
#define IS_CHILD	 0
#define FORK_FAILURE	-1
#define MAXBUFFER 256
#define TRUE 1
#define FALSE 0
#define ASCII_A 65
#define ASCII_T 84
#define READVALUE 60
#define DP1MAX 20
#define DP2Sleep 50000


typedef struct tagHISTOGRAM 
{
    int readHeader; // index for reading values
    int writeHeader; // index for writing values
	char buffer[MAXBUFFER];
} HISTOGRAM;



#ifndef __SEMAPHORE_STRUCT_H__
#define __SEMAPHORE_STRUCT_H__
struct sembuf acquire_operation = { 0, -1, SEM_UNDO };
struct sembuf release_operation = { 0, 1, SEM_UNDO };
unsigned short init_values[1] = { 1 };

#else

extern struct sembuf acquire_operation;
extern struct sembuf release_operation;

#endif