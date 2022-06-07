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

void backStep(Level *level)
{
	unsigned int x = level->playerX;
	unsigned int y = level->playerY;

	switch (level->stepsNode->direction)
	{
	case UP:
		level->map[y-1][x] = PLAYER;
		level->playerY -= 1;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y+1][x] = level->stepsNode->cellReplacedPlus;
		break;
	case DOWN:
		level->map[y+1][x] = PLAYER;
		level->playerY += 1;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y-1][x] = level->stepsNode->cellReplacedPlus;
		break;
	case RIGHT:
		level->map[y][x-1] = PLAYER;
		level->playerX -= 1;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y][x+1] = level->stepsNode->cellReplacedPlus;
		break;
	case LEFT:
		level->map[y][x+1] = PLAYER;
		level->playerX += 1;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y][x-1] = level->stepsNode->cellReplacedPlus;
		break;
	default:
		break;
	}
}

void stepParser(Step **steps, char **str)
{
	// Parser des chaînes comme "URLDLRUDRR"  
}
