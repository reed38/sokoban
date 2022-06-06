#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "steps.h"

static Step *steps = NULL;

void printSteps(void)
{
    // Affiche la pile
    Step *ptrFollow = steps;
    if (NULL == ptrFollow)
		printf("pile vide!");
	else
		printf("Contenu de la pile : \n");
	while (NULL != ptrFollow) {
		printf("DIR = %d \tCR = %c \tCRP = %c\n", ptrFollow->direction, ptrFollow->cellReplaced, ptrFollow->cellReplacedPlus);

		ptrFollow = ptrFollow->previousStep;
	}
	printf("\n");
}

void testSteps(void)
{
    printSteps();
    addStep(&steps, UP, BOX, NOTHING);
    addStep(&steps, UP, BOX, NOTHING);
    addStep(&steps, UP, BOX, NOTHING);
    addStep(&steps, UP, BOX, WALL);
    printSteps();
}