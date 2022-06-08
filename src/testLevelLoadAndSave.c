/**
 * @file testLevelLoadAndSave.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme testant le chargement et la sauvegarde de niveaux en mémoire.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelLoader.h"
#include "levelSaver.h"
#include "steps.h"

static void printLevelsInfo(void);


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
		printf("\tNIVEAU RESOLU : %d\n", ptrFollow->success);
		if(ptrFollow->stepsNode != NULL)
			printf("\tETAPES : %s\n", stepsSerialiser(ptrFollow->stepsNode));
		printf("\tLIGNES TABLEAU : %d\n", ptrFollow->numberLines);
		if(ptrFollow->nextLevel != NULL)
			printf("\tLEVEL SUIVANT : %d\n", ptrFollow->nextLevel->levelNumber);
		else
			printf("\tDERNIER LEVEL\n");
		
		printf("\tMAP ORIGINALE :\n");
		for(int i = 0; i != ptrFollow->numberLines; i++) 
			printf("\t\t%s\n", ptrFollow->defaultMap[i]);
			
		ptrFollow = ptrFollow->nextLevel;
	}
	printf("FIN DES INFOS\n");
}

void testLevelLoadAndSave(void) {

	readLevelsFile("data/level/levels2.lvl");
	printLevelsInfo();

	if(levelsNode == NULL)
    {
        fprintf(stderr, "Besoin d'au moins 1 niveau pour effectuer le test des levels loader/saver...\n");
        return;
    }

	initLevel(levelsNode, 0); // Initialiser le 1er level
	printf("Coordonées x et y du joueur du 1er tableau : %d,%d\n", levelsNode->playerX, levelsNode->playerY);

	printf("Modification du 1er caractère de la 1ère ligne de la map 1 et du score\n");
	levelsNode->map[0][0] = '!';
	levelsNode->numberMov = 980;
	printf("MAP TEMPORAIRE :\n");
	for(int i = 0; i != levelsNode->numberLines; i++) 
		printf("\t\t| %s\n", levelsNode->map[i]);
	printf("SCORE : %d\n", levelsNode->numberMov);

	freeLevel(levelsNode);
	initLevel(levelsNode, 0); // Réinitialiser le 1er level
	printf("Niveau réinitialisée\n");

	printf("MAP TEMPORAIRE :\n");
	for(int i = 0; i != levelsNode->numberLines; i++) 
		printf("\t\t| %s\n", levelsNode->map[i]);
	printf("SCORE : %d\n", levelsNode->numberMov);

	printf("Supression des données temporaires du niveau\n");
	freeLevel(levelsNode);

	//Bloc ajoutant un auteur au 1er niveau
	char *author = "Jean-Dupont de La Clergerie";
	levelsNode->author = (char *) realloc(levelsNode->author, (strlen(author) + 1) * sizeof(char));
	if(levelsNode->author == NULL) 
	{
  		fprintf(stderr, "Mémoire insuffisante !\n");
  		exit(1);
	}
	strcpy(levelsNode->author, author);

	saveLevels("data/level/levels3.lvl");

	printLevelsInfo();
	freeNode();
}