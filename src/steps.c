/**
 * @file steps.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "steps.h"
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
	if(level->stepsNode == NULL)
	{ // Si pas de déplacements enregistrés
		printf("STEPS NULL !\n");
		return;
	}

	unsigned int x = level->playerX;
	unsigned int y = level->playerY;

	switch (level->stepsNode->direction)
	{
	case UP:
		level->map[y+1][x] = PLAYER;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y-1][x] = level->stepsNode->cellReplacedPlus;
		level->playerY += 1;
		break;
	case DOWN:
		level->map[y-1][x] = PLAYER;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y+1][x] = level->stepsNode->cellReplacedPlus;
		level->playerY -= 1;
		break;
	case RIGHT:
		level->map[y][x-1] = PLAYER;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y][x+1] = level->stepsNode->cellReplacedPlus;
		level->playerX -= 1;
		break;
	case LEFT:
		level->map[y][x+1] = PLAYER;
		level->map[y][x] = level->stepsNode->cellReplaced;
		level->map[y][x-1] = level->stepsNode->cellReplacedPlus;
		level->playerX += 1;
		break;
	default:
		break;
	}
	
	Step *step = level->stepsNode;
	level->stepsNode = level->stepsNode->previousStep;
	free(step);
}

void stepsParser(Step **steps, char *str)
{
	//TODO : effectuer les déplacements avec move
	// Parser des chaînes comme "URLDLRUDRR"
	char stringLen = strlen(str);

	for (int i=0; i<stringLen; i++)
	{
		switch (str[i])
		{
		case 'U':
			//move
			addStep(steps, UP, 0, 0);
			break;

		case 'D':
			//move
			addStep(steps, DOWN, 0, 0);
			break;

		case 'L':
			//move
			addStep(steps, LEFT, 0, 0);
			break;
		
		case 'R':
			//move
			addStep(steps, RIGHT, 0, 0);
			break;

		default:
			printf("Erreur dans la chaine de sauvegarde de trajets.\n");
			break;
		}
	}
}
