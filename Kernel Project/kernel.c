#include <stdio.h>
#include "fpga/system_m.h"
#include "kernel.h"

#define MAX_PROCESS 10



typedef struct Descripteur_{
    struct Descripteur_ suivant;
    Process prss;
} Descripteur;

Descripteur readyList[MAX_PROCESS];
unsigned int nbProcess = 0;

void creerProcessus(void (*f), int stackSize, int priority){
    Process p = NULL;
    int* stack = calloc(stackSize, sizeof(int));
    if(stack != NULL){
        p = newProcess((*f), stack, stackSize);
    }
    Descripteur d = { NULL, p };
   if(nbProcess == 0){
       readyList[nbProcess] = d;
       ++nbProcess;
   } else if (nbProcess >= MAX_PROCESS){
       printf("Nombre de processus trop grand, aucun processus peut etre ajoute.");
       exit (EXIT_FAILURE);
   } 
}


int main() {
    return 0;
}
