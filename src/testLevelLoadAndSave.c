/**
 * @file testLevelLoadAndSave.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme testant le chargement et la sauvegarde de niveaux en mémoire
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelLoader.h"
#include "levelSaver.h"

static void printLevelsInfo(void);

// A virer à la fin, sert de débug
/*static void listeAffiche(void)
{
	Level *ptrFollow = levelsNode;

	if (NULL == ptrFollow)
		printf("Liste vide!");
	else
		printf("Contenu de la liste : ");
	while (NULL != ptrFollow) {
		printf("%d ", ptrFollow->levelNumber);

		ptrFollow = ptrFollow->nextLevel;
	}
	printf("\n");
}*/

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

	initLevel(levelsNode); // initaliser le 1er level
	printf("Coordonées x et y du joueur du 1er tableau : %d,%d\n", levelsNode->playerX, levelsNode->playerY);
	printf("Modification du 1er caractère de la 1ère ligne de la map 1\n");
	levelsNode->map[0][0] = '!';
	printf("MAP TEMPORAIRE :\n");
	for(int i = 0; i != levelsNode->numberLines; i++) 
		printf("\t\t| %s\n", levelsNode->map[i]);
	freeLevel(levelsNode);
	printf("Map temporaire supprimée\n");

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