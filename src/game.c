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

	configureTerminal();
	readLevelsFile(argv[1]);

	globalCurrentLevel=levelsNode;
	initLevel(globalCurrentLevel);

	interactionLoop(argv[2]);

    freeLevel(globalCurrentLevel);
    freeNode();

	resetTerminal();

	return 0;
}