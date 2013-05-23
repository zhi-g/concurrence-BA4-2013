/*
 * ex2.c
 *
 *  Created on: 23 May 2013
 *      Author: Valentin Rutz
 */

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <stdio.h>
int main() {
	int reg, temp;
	while (1) {
		reg = IORD_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE);
		if (reg != 0) { //bouton pressé
			temp = reg;
			if (temp % 2 == 1)
				printf("Bouton 1 pressé\n");
			temp = temp / 2;
			if (temp % 2 == 1)
				printf("Bouton 2 pressé\n");
			temp = temp / 2;
			if (temp % 2 == 1)
				printf("Bouton 3 pressé\n");
			temp = temp / 2;
			if (temp % 2 == 1)
				printf("Bouton 4 pressé\n");
			IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTONS_BASE, reg);
			//remet bit à 0
		}
	}
}
