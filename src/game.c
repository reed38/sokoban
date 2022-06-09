/**
 * @file game.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme principal du jeu.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <simple2d.h>

#include "levelLoader.h"
#include "levelSaver.h"
#include "graphics.h"
#include "keys.h"
#include "movements.h"
#include "steps.h"

void render()
{
	S2D_DrawTriangle(
		320, 50, 1, 0, 0, 1,
		540, 430, 0, 1, 0, 1,
		100, 430, 0, 0, 1, 1);
}

/**
 * @brief Fonction d'entrée du programme.
 *
 * @param argc Nombre d'arguments d'éxecution
 * @param argv Tableau des arguments d'éxecution
 * @return Etat de sortie du programme
 */
int main(int argc, char *argv[])
{
#ifdef TEST_LEVEL_LOADER_SAVER
	testLevelLoadAndSave();
	return 0;
#endif
#ifdef TEST_GRAPHICS
	testGraphics();
	return 0;
#endif
#ifdef TEST_MOVEMENTS
	testMovements();
	return 0;
#endif
#ifdef TEST_STEPS
	testSteps();
	return 0;
#endif

	S2D_Window *window = S2D_CreateWindow(
		"Hello Triangle", 640, 480, NULL, render, 0);

	S2D_Show(window);
	return 0;

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

	globalCurrentLevel = levelsNode;
	while (isNextReachable(globalCurrentLevel))
		globalCurrentLevel = globalCurrentLevel->nextLevel;

	initLevel(globalCurrentLevel, 0);

	interactionLoop(argv[2]);

	freeLevel(globalCurrentLevel);
	freeNode();

	resetTerminal();

	return 0;
}