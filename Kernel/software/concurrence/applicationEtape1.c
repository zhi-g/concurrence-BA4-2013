/*
 * Auteur : LSR
 * Date : 2013
 * Goal : Application producteur-consommateur for step 1 of FPGA project
 */

#include <stdio.h>
#include <stdlib.h>
#include "altera_avalon_pio_regs.h"
#include "kernel.h"
#include "system.h"

//Define the buffer size
#define TAILLETAMPON 1
//Define number of buffers (one for each consumer)
#define NBTAMPON 3
//Define duration in which the LED is on and off upon consuming an element from buffers
#define DELAYON 3000000
#define DELAYOFF 300000
//Define process stack size
#define STACKSIZE 10024

//Variable which will keep the id of locks and their conditions which are created (two conditions per lock is needed for this application)
int numVerrou[NBTAMPON] = { 0 };
int numCondition[NBTAMPON][2] = { 0 };

//Variables which are used to define buffers as well as put and get elements into them
int tampon[NBTAMPON][TAILLETAMPON]; //buffers (each has the size of TAILLETAMPON)
int output[NBTAMPON] = { 0 }; //out pointer for each buffer which will increase upon getting a new element
int input[NBTAMPON] = { 0 }; //in pointer for each buffer which will increase upon putting a new element
int nbElement[NBTAMPON] = { 0 }; //number of actual elements in each buffer

//Function which is used by producer to put an element k into buffer t 
void deposer(int t, int k) {
	//Enter the lock with the id numVerrou[t]
	verrouiller(numVerrou[t]);
	//If buffer t is full it should wait
	while (nbElement[t] == TAILLETAMPON) {
		await(numCondition[numVerrou[t]][1]);
	}
	//Put the element k into buffer t
	tampon[t][input[t]] = k;
	input[t] = (input[t] + 1) % TAILLETAMPON;
	nbElement[t]++;
	//Send a signal to everybody waiting on condition numCondition[numVerrou[t],0]
	signal(numCondition[numVerrou[t]][0]);
	//Exit the lock with the id numVerrou[t]
	deverrouiller(numVerrou[t]);
}

//Function which is used by consumer to get an element from buffer t, which will be returned  
int prelever(int t) {
	//Enter the lock with the id numVerrou[t]
	verrouiller(numVerrou[t]);
	//Wait for a signal if the buffer t is empty
	printf("nbElement[%d] = %d\n", t, nbElement[t]);
	while (nbElement[t] == 0) {
		await(numCondition[numVerrou[t]][0]);
	}
	//Get an element from buffer t
	int retour = tampon[t][output[t]];
	output[t] = (output[t] + 1) % TAILLETAMPON;
	nbElement[t]--;
	//Send a signal to everybody waiting on condition numCondition[numVerrou[t],1]
	signal(numCondition[numVerrou[t]][1]);
	//Exit the lock with the id numVerrou[t]
	deverrouiller(numVerrou[t]);
	//Return the element which is already taken from buffer t
	return retour;
}

//Producer function which upon pressing any of the buttons 0,1 or 2
//will add element '1' to buffers 0,1 or 2 respectively
void producteur(void) {
	//Infinite loop to read from buttons and put elements into corresponding buffers
	while (1) {
		//read which button is pressed by returning the value of button register
		int buttons = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);
		int temp=0;
		int j=0;
		temp = buttons;
		//To reinitialize the buttons register before reading new buttons
		IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, buttons);
		//To verify which buttons are pressed
		for (j = 0; j < NBTAMPON; j++) {
			if (temp % 2 == 1)
				deposer(j, 1); //To put element 1 into buffer j because button j is pressed
			temp >>= 1;
		}

	}
}

//First consumer function which will make led 0 blink upon getting an element from buffer 0 
void consommateur0(void) {
	//Infinite loop to read from buffer 0
	while (1) {
		// Get an element from buffer 0 (if there is no element, it will go to wait on this line)
		prelever(0);
		// Blink led 0 for specfied duration (one blink means consuming one element from buffer 0)
		int i=0;
		IOWR_ALTERA_AVALON_PIO_DATA(LED_0_BASE, 1);
		//turn on the first bit of led 0 for specified duration
		while (i < DELAYON) {
			i++;
		}
		i = 0;
		IOWR_ALTERA_AVALON_PIO_DATA(LED_0_BASE, 0);
		//turn off the first bit of led 0 for specified duration
		while (i < DELAYOFF) {
			i++;
		}
		i = 0;
	}


}

//Second consumer function which will make led 1 blink upon getting an element from buffer 1 
void consommateur1(void) {
	//Infinite loop to read from buffer 1
	while (1) {
		// Get an element from buffer 1 (if there is no element, it will go to wait on this line)
		prelever(1);
		// Blink led 1 for specfied duration (one blink means consuming one element from buffer 1)
		int i=0;
		IOWR_ALTERA_AVALON_PIO_DATA(LED_1_BASE, 1);
		//turn on the first bit of led 1 for specified duration
		while (i < DELAYON) {
			i++;
		}
		i = 0;
		IOWR_ALTERA_AVALON_PIO_DATA(LED_1_BASE, 0);
		//turn off the first bit of led 1 for specified duration
		while (i < DELAYOFF) {
			i++;
		}
		i = 0;
	}
}

//Third consumer function which will make led 2 blink upon getting an element from buffer 2 
void consommateur2(void) {
	//Infinite loop to read from buffer 2
	while (1) {
		// Get an element from buffer 2 (if there is no element, it will go to wait on this line)
		prelever(2);
		// Blink led 2 for specfied duration (one blink means consuming one element from buffer 2)
		int i=0;
		IOWR_ALTERA_AVALON_PIO_DATA(LED_2_BASE, 1);
		//turn on the first bit of led 2 for specified duration
		while (i < DELAYON) {
			i++;
		}
		i = 0;
		IOWR_ALTERA_AVALON_PIO_DATA(LED_2_BASE, 0);
		//turn off the first bit of led 2 for specified duration
		while (i < DELAYOFF) {
			i++;
		}
		i = 0;
	}
}

//Main program
int main() {
	//Initialize leds and buttons
	IOWR_ALTERA_AVALON_PIO_DATA(LED_0_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_DATA(LED_1_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_DATA(LED_2_BASE, 0);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, 15);
	//Create the locks and save their ids in numVerrou array
	numVerrou[0] = creerVerrou();
	numVerrou[1] = creerVerrou();
	numVerrou[2] = creerVerrou();
	//Create conditions (0: notempty condition, 1: notfull condition) and save their ids in creerCondition array, linked to their corresponding locks
	numCondition[numVerrou[0]][0] = creerCondition(numVerrou[0]);
	numCondition[numVerrou[0]][1] = creerCondition(numVerrou[0]);
	numCondition[numVerrou[1]][0] = creerCondition(numVerrou[1]);
	numCondition[numVerrou[1]][1] = creerCondition(numVerrou[1]);
	numCondition[numVerrou[2]][0] = creerCondition(numVerrou[2]);
	numCondition[numVerrou[2]][1] = creerCondition(numVerrou[2]);
	//Create the processes
	creerProcessus(producteur, STACKSIZE, 1);
	creerProcessus(consommateur0, STACKSIZE, 2);
	creerProcessus(consommateur1, STACKSIZE, 2);
	creerProcessus(consommateur2, STACKSIZE, 2);
	//Start execution of the processes
	start();
	return 0;
}

