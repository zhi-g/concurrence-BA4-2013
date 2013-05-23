#include <stdio.h>
#include <stdlib.h>
#include "fpga/system_m.h"
#include "kernel.h"

#define MAX_PROCESS 10
#define MAX_LOCK 10
#define MAX_COND 10

typedef struct {
    int priority;
    Process p;
    int nextInLock;
    int nextInCond;
} ProcessDescriptor;

ProcessDescriptor processes[MAX_PROCESS];
unsigned int nextProcess = 0;
int readyList = -1;

typedef struct {
	int condID;
	int waitingList;
} ConditionDescriptor;

typedef struct {
	int state; // 0 => closed and 1 => open
	int waitingList;
	int lockID;
	ConditionDescriptor conds[MAX_COND];
	unsigned int nbCond;
} LockDescriptor;

LockDescriptor locks[MAX_LOCK];
unsigned int nextLock = 0;

/***********************************************************
 ***********************************************************
            Utility functions for list manipulation
************************************************************
* **********************************************************/

// add element to the tail of the list
void addLast(int* list, int processId) {

    if (*list == -1){
        // list is empty
        *list = processId;
    }
    else {
        int temp = *list;
        while (processes[temp].next != -1){
            temp = processes[temp].next;
        }
        processes[temp].next = processId;
        processes[processId].next = -1;
    }

}

// add element to the head of list
void addFirst(int* list, int processId){

    if (*list == -1){
        *list = processId;
    }
    else {
        processes[processId].next = *list;
        *list = processId;
    }
}

// remove element that is head of the list
int removeHead(int* list){
    if (*list == -1){
        printf("List is empty!");
        return(-1);
    }
    else {
        int head = *list;
        int next = processes[*list].next;
        processes[*list].next = -1;
        *list = next;
        return head;
    }
}

// returns head of the list
int head(int* list){
    if (*list == -1){
        printf("List is empty!\n");
        return(-1);
    }
    else {
        return *list;
    }
}

void creerProcessus(void (*f), int stackSize, int priority){
	if (nbProcess >= MAX_PROCESS) {
		printf("Error: max number of processes reached!\n");
		exit(1);
	}
    Process p = NULL;
    unsigned int* stackAddr = NULL;
    stackAddr = calloc(stackSize, sizeof(int));
    
    if(stackAddr != NULL) {
        p = newProcess(f, stackAddr, stackSize);
        
        if(p != NULL) {
        	//TODO: rajout de p dans tab de process et dans la ready list
            nbProcess++;
        }
    }
}
