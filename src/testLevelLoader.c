/**
 * @file testLevelLoader.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme testant le chargeant les niveaux en mémoire.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelLoader.h"

static void freeNode(void);
static void printLevelsInfo(void);

// Parceque voir aucune fuite de mémoires avec valgrind ça fait plaisir
static void freeNode(void) 
{
	Level *ptrFollow = levelsNode;
	Level *precPtdr = NULL;

	while (ptrFollow != NULL) 
	{        
		for(int i = 0; i != ptrFollow->numberLines; i++) 
		{
			//printf("Supression map lv %d, ligne %d\n", ptrFollow->levelNumber, i);
			free(ptrFollow->map[i]);
		}
		free(ptrFollow->map);
		free(ptrFollow->author);
		free(ptrFollow->comment);
		precPtdr = ptrFollow;
		ptrFollow = ptrFollow->nextLevel;
		free(precPtdr);
		//printf("Supression du lv terminee !\n");
	}
}

/**
 * @brief Affiche toutes les informations sur la file contenant les niveaux en mémoire.
 */
static void printLevelsInfo(void)
{
	Level *ptrFollow = levelsNode;

	while (ptrFollow != NULL) 
	{
		printf("INFOS LEVEL %d :\n", ptrFollow->levelNumber);
		if(ptrFollow->author != NULL)
			printf("\tAUTEUR : %s\n", ptrFollow->author);
		if(ptrFollow->comment != NULL)
			printf("\tCOMMENTAIRE : %s\n", ptrFollow->comment);
		printf("\tLIGNES TABLEAU : %d\n", ptrFollow->numberLines);
		if(ptrFollow->nextLevel != NULL)
			printf("\tLEVEL SUIVANT : %d\n", ptrFollow->nextLevel->levelNumber);
		else
			printf("\tDERNIER LEVEL\n");
		
		printf("\tMAP :\r");
		for(int i = 0; i != ptrFollow->numberLines; i++) 
			printf("\t\t%s\n", ptrFollow->map[i]);
			
		ptrFollow = ptrFollow->nextLevel;
	}
	printf("FIN DES INFOS\n");
}

void testLevelLoader(void) {
	readLevelsFile("data/level/levels.lvl");
	printLevelsInfo();

	determinePlayerCoord(levelsNode); // 1er level
	printf("Coordonées x et y du joueur du 1er tableau : %d,%d\n", levelsNode->playerX, levelsNode->playerY);

	freeNode();
}