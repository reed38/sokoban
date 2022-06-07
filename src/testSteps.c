#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelLoader.h"
#include "steps.h"

static void printMap(char ***map)
{
    for(int i = 0; i != levelsNode->numberLines; i++) 
	printf("\t\t| %s\n", levelsNode->map[i]);
}

static void printSteps(Step *stepsNode)
{
    // Affiche la pile
    Step *ptrFollow = stepsNode;
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
    readLevelsFile("data/level/levels2.lvl");

	if(levelsNode == NULL)
    {
        fprintf(stderr, "Besoin d'au moins 1 niveau pour effectuer le test des levels loader/saver...\n");
        return;
    }

    initLevel(levelsNode); // initialiser le 1er level
    
    printSteps(levelsNode->stepsNode);
    addStep(&levelsNode->stepsNode, UP, NOTHING, WALL);
    addStep(&levelsNode->stepsNode, LEFT, NOTHING, NOTHING);
    addStep(&levelsNode->stepsNode, LEFT, NOTHING, NOTHING);
    addStep(&levelsNode->stepsNode, LEFT, NOTHING, NOTHING);
    addStep(&levelsNode->stepsNode, LEFT, NOTHING, NOTHING);
    addStep(&levelsNode->stepsNode, LEFT, NOTHING, BOX);
    addStep(&levelsNode->stepsNode, LEFT, BOX, NOTHING);
    printSteps(levelsNode->stepsNode);

    printMap()

    backStep(levelsNode);
    backStep(levelsNode);
    backStep(levelsNode);
    backStep(levelsNode);
    backStep(levelsNode);
    backStep(levelsNode);
    backStep(levelsNode);
    printSteps(levelsNode->stepsNode);
   
    for(int i = 0; i != levelsNode->numberLines; i++) 
		printf("\t\t| %s\n", levelsNode->map[i]);

    
    /*
    stepsParser(&steps, "UUUUUUD");
    */
}