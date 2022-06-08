#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"
#include "pathfinding.h"
#define TRAVERSABLE 1
#define NOTTRAVERSABLE 0
static void initializeSurrounding(Node **node, Level *level, unsigned int x, unsigned int y, int xTarget, int yTarget);
static void initializeNode(Node **node, unsigned int x, unsigned int y, unsigned int lastValue, int xTarget, int yTarget);
unsigned int *findMin(unsigned int *ptr, Node **node);
static char doesExist(unsigned int x, unsigned int y);

Node **convertToNode(Level *level)
{
    char **map = level->map;
    Node **tabNode = malloc(sizeof(Node *) * (level->numberLines));
    for (int i = 0; i < level->numberLines; i++)
    {
        tabNode[i] = malloc(sizeof(Node) * (strlen(level->map[i])) + 1);
    }
    for (unsigned int i = 0; i < level->numberLines; i++)
    {
        for (unsigned int j = 0; j < strlen(level->map[i]); j++)
        {
            if (map[i][j] == BOX || map[i][j] == WALL || map[i][j] == FULLBOX)
            {
                tabNode[i][j].type = NOTTRAVERSABLE;
            }
            else
            {
                tabNode[i][j].type = TRAVERSABLE;
            }
            tabNode[i][j].gCost = 0;
            tabNode[i][j].hCost = 0;
            tabNode[i][j].total_cost = 0;
            tabNode[i][j].isOpen = 1;
        }
    }
    return tabNode;
}

void printfGraph(Node **node, Level *level)

{
    for (unsigned int i = 0; i < level->numberLines; i++)
    {
        for (unsigned int j = 0; j < strlen(level->map[i]); j++)
        {
            // printf("%u_%u_%u_%d_%d ", node[i][j].gCost, node[i][j].hCost, node[i][j].total_cost, (int)node[i][j].isOpen, (int)node[i][j].type);
            printf("%d ", node[i][j].total_cost);
        }
        printf("\n");
    }
    printf("\n");
}

static char doesExist(unsigned int x, unsigned int y)
{

    if (y < globalCurrent->numberLines && x < strlen(globalCurrent->map[y]) && x >= 0 && y >= 0)
        return 1;
    else
        return 0;
}

static void initializeNode(Node **node, unsigned int x, unsigned int y, unsigned int lastValue, int xTarget, int yTarget) // position 0 pour diagonale 1 autrement
{
    if (doesExist(x, y))
    {
        if (node[y][x].isOpen == 1 && node[y][x].type == TRAVERSABLE)
        {
            node[y][x].hCost =(int) sqrt((x - xTarget) * (x - xTarget) + (y - yTarget) * (y - yTarget));

            node[y][x].gCost += 1;

            node[y][x].total_cost = node[y][x].hCost + node[y][x].gCost;
        }
    }
}

static void initializeSurrounding(Node **node, Level *level, unsigned int x, unsigned int y, int xTarget, int yTarget)
{

    initializeNode(node, x, y + 1, node[y][x].gCost, xTarget, yTarget);
    initializeNode(node, x, y - 1, node[y][x].gCost, xTarget, yTarget);
    initializeNode(node, x - 1, y, node[y][x].gCost, xTarget, yTarget);
    initializeNode(node, x + 1, y, node[y][x].gCost, xTarget, yTarget);
}

unsigned int *findMin(unsigned int *result, Node **node)
{
    unsigned int currentMin = MAXUNSIGNED;
    for (int i = 0; i < globalCurrent->numberLines; i++)
    {
        for (int j = 0; j < strlen(globalCurrent->map[i]); j++)
        {
            if (node[i][j].total_cost < currentMin && node[i][j].total_cost > 0 && node[i][j].isOpen == 1 && node[i][j].type == TRAVERSABLE)
            {
                currentMin = node[i][j].total_cost;
                result[0] = i;
                result[1] = j;
            }
        }
    }
    node[result[1]][result[0]].isOpen = 0;

    return result;
}

void pathfinding(Node **graph, unsigned int xStart, unsigned int yStart, unsigned int xTarget, unsigned int yTarget)
{

    Node *currentNode = &graph[yStart][xStart];

    unsigned int *nodeCoordinates = malloc(sizeof(unsigned int) * 2);
    nodeCoordinates[1] = xStart;
    nodeCoordinates[0] = yStart;
    currentNode->hCost = sqrt((xStart - xTarget) * (xStart - xTarget) + (yStart - yTarget) * (yStart - yTarget));
    currentNode->isOpen = 0;
    currentNode->total_cost = 2;
    // while (currentNode != &graph[xTarget][yTarget])
    for (int i = 0; i < 1; i++)
    {
        initializeSurrounding(graph, globalCurrent, nodeCoordinates[1], nodeCoordinates[0], xTarget, yTarget);
        nodeCoordinates = findMin(nodeCoordinates, graph);
    }
    free(nodeCoordinates);
}
