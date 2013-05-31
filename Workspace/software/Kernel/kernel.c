#include <stdio.h>
#include <stdlib.h>
#include "system_m.h"
#include "kernel.h"

#define MAX_PROCESS 4
#define MAX_LOCK 3
#define MAX_COND 2

typedef struct {
	int priority;
	Process p;
	int next;
} ProcessDescriptor;

ProcessDescriptor processes[MAX_PROCESS];
unsigned int nbProcess = 0;
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
	int lockingPrss;
	int nestingDepth;
} LockDescriptor;

LockDescriptor locks[MAX_LOCK];
unsigned int nbLocks = 0;

/***********************************************************
 ***********************************************************
 Utility functions for list manipulation
 ************************************************************
 * **********************************************************/
// add element to the head of list
void addFirst(int* list, int processId) {

	if (*list == -1) {
		*list = processId;
	} else {
		processes[processId].next = *list;
		*list = processId;
	}
}

// add element to the tail of the list
void addLast(int* list, int processId) {
	//printf("enter: add last\n");
	if (*list == -1) {
		// list is empty
		*list = processId;

	} else {
		int temp = *list;
		while (processes[temp].next != -1) {
			temp = processes[temp].next;
		}
		processes[temp].next = processId;
		processes[processId].next = -1;
	}

}

// remove element that is head of the list
int removeHead(int* list) {
	if (*list == -1) {
		printf("List is empty!\n");
		return (-1);
	} else {
		int head = *list;
		int next = processes[*list].next;
		processes[*list].next = -1;
		*list = next;
		return head;
	}
}

// returns head of the list
int head(int* list) {
	if (*list == -1) {
		printf("List is empty!\n");
		fflush(stdout);
		return (-1);
	} else {
		return *list;
	}
}

int priorityHead(int* list) {
	if (*list == -1) {
		printf("List is empty!\n");
		fflush(stdout);
		return (-1);
	} else {
		int temp = *list;
		while (processes[temp].next != -1 && processes[temp].priority < 2) {
			temp = processes[temp].next;
		}

		return temp;
	}
}
int removePriorityHead(int* list) {
	if (*list == -1) {
		printf("List is empty!\n");
		fflush(stdout);
		return (-1);
	} else {
		int temp = *list;
		int previous = -1;
		while (processes[temp].next != -1 && processes[temp].priority < 2) {
			previous = temp;
			temp = processes[temp].next;
		}
		if (previous == -1) {

			*list = processes[temp].next;
		} else {
			processes[previous].next = processes[temp].next;
		}
		processes[temp].next = -1;
		return temp;
	}
}
/**************************************************************
 * 					KERNEL
 ***************************************************************/

void creerProcessus(void (*f), int stackSize, int priority) {
	//printf("Creation de processus de priority %d\n", priority);
	if (nbProcess >= MAX_PROCESS) {
		printf("Error: max number of processes reached!\n");
		exit(1);
	}

	unsigned int* stackAddr = malloc(stackSize);
	//  printf("Stack for process no %d stack at address:\n ", nbProcess);

	Process p = newProcess(f, stackAddr, stackSize);
	processes[nbProcess].p = p;
	processes[nbProcess].priority = priority;
	processes[nbProcess].next = -1;
	addLast(&readyList, nbProcess);
	nbProcess++;

	//  printf("End of creation \n");
}

void start() {
	printf("Starting kernel...\n");
	if (readyList == -1) {
		printf("Error: No process in the ready list!\n");
		exit(1);
	}
	Process process = processes[priorityHead(&readyList)].p;
	transfer(process);
}

int creerVerrou() {
	if (nbLocks >= MAX_LOCK) {
		printf("Error: max number of locks reached!\n");
		exit(1);
	}
	locks[nbLocks].lockID = nbLocks;
	locks[nbLocks].state = 1;
	locks[nbLocks].waitingList = -1;
	locks[nbLocks].nbCond = 0;
	locks[nbLocks].lockingPrss = -1;
	locks[nbLocks].nestingDepth = 0;

	int n = nbLocks;
	nbLocks++;
	return n;
}

void verrouiller(int verrouID) {
	if (locks[verrouID].state == 1
			|| locks[verrouID].lockingPrss == priorityHead(&readyList)) {
		locks[verrouID].state = 0;
		/*if(locks[verrouID].lockingPrss == priorityHead(&readyList)){
		 locks[verrouID].nestingDepth++;
		 }else{
		 locks[verrouID].nestingDepth=1;
		 }*/
		locks[verrouID].nestingDepth++;
		locks[verrouID].lockingPrss = priorityHead(&readyList);
	} else {
		int prss = removePriorityHead(&readyList);
		addLast(&locks[verrouID].waitingList, prss);
		if (processes[prss].priority < 2) {
			processes[prss].priority = 3;
		}
		transfer(processes[priorityHead(&readyList)].p);
	}
}

void deverrouiller(int verrouID) {
	if (locks[verrouID].nestingDepth > 0) {
		locks[verrouID].state = 1;
		if (processes[locks[verrouID].lockingPrss].priority == 3) {
			processes[locks[verrouID].lockingPrss].priority = 1;
		}
		int tmp = locks[verrouID].lockingPrss;
		locks[verrouID].lockingPrss = -1;
		locks[verrouID].nestingDepth--;
		if (locks[verrouID].nestingDepth == 0
				&& locks[verrouID].waitingList != -1) {
			int p = removeHead(&locks[verrouID].waitingList);
			addLast(&readyList, p);
			locks[verrouID].lockingPrss = p;
			locks[verrouID].state = 0;

			if (processes[p].priority - 1 >= processes[tmp].priority) {
				transfer(processes[priorityHead(&readyList)].p);
			}

		}
	}
}

int creerCondition(int verrouID) {
	if (locks[verrouID].nbCond >= MAX_COND) {
		printf("Error: max number of conditions for lock %d reached!\n",
				verrouID);
		exit(1);
	}
	locks[verrouID].conds[locks[verrouID].nbCond].condID = verrouID * MAX_COND
			+ locks[verrouID].nbCond; //expliquer
	locks[verrouID].conds[locks[verrouID].nbCond].waitingList = -1;
	locks[verrouID].nbCond++;
	return locks[verrouID].conds[locks[verrouID].nbCond - 1].condID;
}

//
void await(int conditionID) {
	int lockID = conditionID / MAX_COND;
	int p = removePriorityHead(&readyList);
	addLast(&(locks[lockID].conds[conditionID % MAX_COND].waitingList), p);
	deverrouiller(lockID);
	transfer(processes[priorityHead(&readyList)].p);

}

void signal(int conditionID) {
	int lockID = conditionID / MAX_COND;
	int p = removeHead(
			&locks[lockID].conds[conditionID % MAX_COND].waitingList);
	if (p != -1) {
		addFirst(&locks[lockID].waitingList, p);
	}

}

void signalAll(int conditionID) {
	int lockID = conditionID / MAX_COND;
	while (locks[lockID].conds[conditionID % MAX_COND].waitingList != -1) {
		signal(conditionID);

	}
}
