/*
 * IMPLEMENTATION DE L'ALGORITHME A*
 * NE FONCTIONNE PAS
 * NON INTEGRE DANS LE JEU
 */
#define TRAVERSABLE 1
#define NOTTRAVERSABLE 0
#define MAX 999999

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"
#include "pathfinding.h"

/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/

static int globalUnexploredNodes = 0;


/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static void initializeSurrounding(Node **tab, int x, int y, int lastValue, int xTarget, int yTarget);
static void initializeNode(Node **tab, int x, int y, int lastValue, int xTarget, int yTarget);
Node *findMin(Node **node);
char doesExist(int x, int y);
int manathanDistance(int x1, int y1, int x2, int y2);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

Node **convertToNode(Level *level)
{
	char **map = level->map;
	Node **tabNode = malloc(sizeof(Node *) * (level->numberLines));
	if (levelsNode == NULL)
	{
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}
	for (int i = 0; i < level->numberLines; i++)
	{
		tabNode[i] = malloc(sizeof(Node) * (strlen(level->map[i])) + 1);
		if (tabNode[i] == NULL)
		{
			fprintf(stderr, "Mémoire insuffisante !\n");
			exit(1);
		}
	}
	for (int i = 0; i < level->numberLines; i++)
	{
		for (int j = 0; j < strlen(level->map[i]); j++)
		{
			tabNode[i][j].x = j;
			tabNode[i][j].y = i;
			if (map[i][j] == BOX 
                || map[i][j] == WALL
			    || map[i][j] == FULLBOX)
			{
				tabNode[i][j].isOpen = 3;
				tabNode[i][j].hCost = 0;
				tabNode[i][j].fCost = 0;
			}
			else
			{
				tabNode[i][j].isOpen = 0;
				tabNode[i][j].gCost = 0;
				tabNode[i][j].hCost = 0;
				tabNode[i][j].fCost = 0;
				globalUnexploredNodes += 1;
			}
		}
	}
	return tabNode;
}

void printfGraph(Node **node, Level *level)
{
	for (int i = 0; i < level->numberLines; i++)
	{
		for (int j = 0; j < strlen(level->map[i]); j++)
		{
			// printf("%u_%u_%u_%d_%d ", node[i][j].gCost, node[i][j].hCost, node[i][j].fCost, (int)node[i][j].isOpen, (int)node[i][j].type);
			printf("%d ", node[i][j].isOpen);
		}
		printf("\n");
	}
	printf("\n");
}

int manathanDistance(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

static void initializeNode(Node **tab, int x, int y, int lastGvalue,
			   int xTarget, int yTarget)
{
	if (tab[y][x].isOpen != 3)
	{
		int newhCost = manathanDistance(x, xTarget, y, yTarget);
		int newgCost = lastGvalue + 1;
		int newfCost = newgCost + newhCost;
		if (tab[y][x].isOpen == 0)
		{
			tab[y][x].hCost = newhCost;
			tab[y][x].gCost = newgCost;
			tab[y][x].fCost = newfCost;
			tab[y][x].isOpen = 1;
		}
		else if (tab[y][x].isOpen == 1 && tab[y][x].fCost > newfCost)
		{

			tab[y][x].hCost = newhCost;
			tab[y][x].gCost = newgCost;
			tab[y][x].fCost = newfCost;
		}
		else if (tab[y][x].isOpen == 2 && tab[y][x].fCost > newfCost)
		{
			tab[y][x].isOpen = 1;
		}
	}
}

static void initializeSurrounding(Node **tab, int x, int y, int lastValue, int xTarget, int yTarget)
{

	initializeNode(tab, (x - 1), y, lastValue, xTarget, yTarget);
	initializeNode(tab, (x + 1), y, lastValue, xTarget, yTarget);
	initializeNode(tab, x, (y - 1), lastValue, xTarget, yTarget);
	initializeNode(tab, x, (y + 1), lastValue, xTarget, yTarget);
}

Node *findMin(Node **node)
{
	int currentMin = MAX;
	Node *result;
	for (int i = 0; i < globalCurrentLevel->numberLines; i++)
	{
		for (int j = 0; j < strlen(globalCurrentLevel->map[i]); j++)
		{
			// printf("%u_%u_%u_%d_%d \n", node[i][j].gCost, node[i][j].hCost, node[i][j].fCost, (int)node[i][j].isOpen, (int)node[i][j].type);
			if (node[i][j].isOpen == 1
			    && node[i][j].fCost < currentMin)
			{
				currentMin = node[i][j].fCost;
				result = &node[i][j];
				result->isOpen = 2;

			}
		}
	}
	return result;
}

void pathfinding(Node **graph, int xStart, int yStart, int xTarget,
		 int yTarget)
{
	Node startNode = graph[yStart][xStart];
	// Node *endNode = &graph[yTarget][xTarget];
	Node *currentNode = &startNode;
	startNode.gCost = 0;
	startNode.hCost = manathanDistance(xStart, yStart, xTarget, yTarget);
	startNode.fCost = startNode.gCost + startNode.hCost;
	// while (globalUnexploredNodes > 0 && currentNode != endNode)
	for (int i = 0; i < 500; i++)
	{
		initializeSurrounding(graph, currentNode->x, currentNode->y, currentNode->gCost, xTarget, yTarget);
		currentNode = findMin(graph);
	}
	if (globalUnexploredNodes == 0)
	{
		printf("pas de solutions");
	}
}