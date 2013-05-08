#ifndef KERNEL_H_
#define KERNEL_H_

void creerProcessus(void (*f), int stackSize, int priority);

void start();

int creerVerrou();

int creerCondition(int verrouID);

void verrouiller(int verrouID);

void deverrouiller(int verrouID);

void await(int conditionID);

void signal(int conditionID);

void signalAll(int conditionID);

int timedAwait(int conditionID, int time);

#endif /*KERNEL_H_*/
