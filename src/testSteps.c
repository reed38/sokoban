/**
 * @file steps.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme de test de la gestion de l'historique des déplacements.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelLoader.h"
#include "levelSaver.h"
#include "steps.h"
#include "keys.h"
#include "movements.h"

static void printMap(char **map, unsigned int nbLines);
static void printSteps(Step *stepsNode);

void testSteps(void)
{
	readLevelsFile("data/level/levels2-steps.lvl");

	Level *level1 = levelsNode;
	Level *level2 = levelsNode->nextLevel;

	if (level1 == NULL && level2 == NULL)
	{
		fprintf(stderr, "Besoin d'au moins 2 niveaux pour effectuer le test d'enregistrement des déplacements...\n");
		return;
	}

	// Tests de la pile
	printf("-- TEST DE LA PILE DE STEPS\n");
	printf("LEVEL1 \n");
	initLevel(levelsNode, 0);	// Initialiser le 1er level

	printSteps(level1->stepsNode);
	// On simule quelques déplacements
	addStep(&level1->stepsNode, UP, NOTHING, WALL);
	addStep(&level1->stepsNode, LEFT, NOTHING, NOTHING);
	addStep(&level1->stepsNode, LEFT, NOTHING, NOTHING);
	addStep(&level1->stepsNode, LEFT, NOTHING, NOTHING);
	addStep(&level1->stepsNode, LEFT, NOTHING, NOTHING);
	addStep(&level1->stepsNode, LEFT, NOTHING, BOX);
	addStep(&level1->stepsNode, LEFT, BOX, NOTHING);
	printSteps(level1->stepsNode);

	printMap(level1->map, level1->numberLines);

	for (int i = 0; i < 7; i++)
		backStep(level1);

	printSteps(level1->stepsNode);

	printMap(level1->map, level1->numberLines);

	freeLevel(level1);

	printf("LEVEL2 \n");
	initLevel(level2, 0);	// Initialiser le 2nd level

	printSteps(level2->stepsNode);
	// On simule quelques déplacements
	addStep(&level2->stepsNode, DOWN, TARGET, TARGET);
	addStep(&level2->stepsNode, RIGHT, NOTHING, NOTHING);
	addStep(&level2->stepsNode, RIGHT, NOTHING, NOTHING);
	addStep(&level2->stepsNode, RIGHT, NOTHING, NOTHING);
	addStep(&level2->stepsNode, RIGHT, NOTHING, NOTHING);
	addStep(&level2->stepsNode, RIGHT, NOTHING, NOTHING);
	addStep(&level2->stepsNode, RIGHT, NOTHING, NOTHING);
	printSteps(level2->stepsNode);

	printMap(level2->map, level2->numberLines);

	for (int i = 0; i < 7; i++)
		backStep(level2);

	printSteps(level2->stepsNode);

	printMap(level2->map, level2->numberLines);

	// Tests parser / serialiser
	printf("-- TEST DU STEP PARSER/SERIALISER\n");

	stepsParser(&level2->stepsNode, "124");
	stepsParser(&level2->stepsNode, "1aa24");
	char *serializedSteps = stepsSerialiser(level2->stepsNode);
	printf("Chaine sérialisée : %s\n", serializedSteps);
	free(serializedSteps);
	printSteps(level2->stepsNode);

	freeLevel(level2);
	freeNode();
}

static void printMap(char **map, unsigned int nbLines)
{
	for (int i = 0; i != nbLines; i++)
		printf("\t\t| %s\n", map[i]);
}

static void printSteps(Step *stepsNode)
{
	// Affiche la pile
	Step *ptrFollow = stepsNode;
	if (NULL == ptrFollow)
		printf("pile vide!");
	else
		printf("Contenu de la pile : \n");
	while (NULL != ptrFollow)
	{
		printf("DIR = %d \tCR = %c \tCRP = %c\n", ptrFollow->direction, ptrFollow->cellReplaced, ptrFollow->cellReplacedPlus);

		ptrFollow = ptrFollow->previousStep;
	}
	printf("\n");
}