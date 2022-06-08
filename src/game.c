/**
 * @file game.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme principal du jeu.
 * 
 */
#include <stdlib.h>
#include <stdio.h>

#include "levelLoader.h"
#include "levelSaver.h"
#include "graphics.h"
#include "keys.h"
#include "movements.h"


int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		fprintf(stderr, "Mauvaise utilisation de la commande... Utilisez : %s [fichier de niveaux] [fichier de sauvegarde]\n", argv[0]);
		return 1;
	}
	printf("Chargement...\n");

	readLevelsFile(argv[1]);
	if (levelsNode == NULL)
	{
		fprintf(stderr, "Fichier d'entrée incorrect\n");
		return 1;
	}

	configureTerminal();
	
	globalCurrentLevel=levelsNode;
	initLevel(globalCurrentLevel);

	interactionLoop(argv[2]);

    freeLevel(globalCurrentLevel);
    freeNode();

	resetTerminal();

	return 0;
}