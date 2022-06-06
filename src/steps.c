/**
 * @file steps.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelLoader.h"

/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

void addStep(Step **steps, unsigned char direction, unsigned char cellReplaced, unsigned char cellReplacedPlus)
{
	Step *step = malloc(sizeof(Step));
	if(step == NULL) {
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}

	step->direction = direction;
	step->cellReplaced = cellReplaced;
	step->cellReplacedPlus = cellReplacedPlus;
	step->previousStep = *steps;

	*steps = step;
}

void stepParser(Step **steps, char **str)
{
	// Parser des chaînes comme "URLDLRUDRR"  
}
