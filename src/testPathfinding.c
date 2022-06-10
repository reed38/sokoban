#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pathfinding.h"
#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"

void testPathfinding(void)
{
	char *levelFile = "data/level/levels.lvl";	// Besoin d'au moins 2 niveaux
	readLevelsFile(levelFile);
	if (levelsNode == NULL && levelsNode->nextLevel == NULL)
	{
		fprintf(stderr, "Besoin d'au moins 2 niveaux pour effectuer le test des levels loader/saver...\n");
		return;
	}

	globalCurrentLevel = levelsNode->nextLevel;
	initLevel(globalCurrentLevel, 0);
	Node **graph = convertToNode(globalCurrentLevel);
	printfGraph(graph, globalCurrentLevel);

	pathfinding(graph, 1, 1, 9, 1);
	printfGraph(graph, globalCurrentLevel);

	for (int i = 0; i < globalCurrentLevel->numberLines; i++)
	{
		free(graph[i]);
	}

	free(graph);
	// configureTerminal();
	// interactionLoop();
}