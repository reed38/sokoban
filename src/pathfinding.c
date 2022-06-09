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
static void initializeSurrounding(Node **tab,  int x,   int y,  int lastValue, int xTarget, int yTarget);
static void initializeNode(Node **tab,   int x,  int y,   int lastValue,   int xTarget,   int yTarget);
Node *findMin(Node **node);
char doesExist( int x,  int y);

char doesExist( int x,  int y)
{

    if (y < globalCurrent->numberLines && x < strlen(globalCurrent->map[y]) && x >= 0 && y >= 0)
        return 1;
    else
        return 0;
}

Node **convertToNode(Level *level)
{
    char **map = level->map;
    Node **tabNode = malloc(sizeof(Node *) * (level->numberLines));
    for (int i = 0; i < level->numberLines; i++)
    {
        tabNode[i] = malloc(sizeof(Node) * (strlen(level->map[i])) + 1);
    }
    for (  int i = 0; i < level->numberLines; i++)
    {
        for (  int j = 0; j < strlen(level->map[i]); j++)
        {
            tabNode[i][j].x = j;
            tabNode[i][j].y = i;
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
    for (  int i = 0; i < level->numberLines; i++)
    {
        for (  int j = 0; j < strlen(level->map[i]); j++)
        {
            // printf("%u_%u_%u_%d_%d ", node[i][j].gCost, node[i][j].hCost, node[i][j].total_cost, (int)node[i][j].isOpen, (int)node[i][j].type);
            printf("%d ", node[i][j].total_cost);
        }
        printf("\n");
    }
    printf("\n");
}



static void initializeNode(Node **tab,   int x,  int y,   int lastValue,   int xTarget,   int yTarget) // position 0 pour diagonale 1 autrement
{
    if (doesExist((int) x, (int) y)==1)
    {
        if (tab[x][y].isOpen== 1 && tab[x][y].type == TRAVERSABLE)
        {
            tab[x][y].hCost = (int)sqrt((x - xTarget) * (x - xTarget) + (y - yTarget) * (y - yTarget));

            tab[x][y].gCost = lastValue + 1;

            tab[x][y].total_cost = tab[x][y].hCost + tab[x][y].gCost;
        }
    }
}

static void initializeSurrounding(Node **tab,  int x,   int y,  int lastValue, int xTarget, int yTarget)
{

    initializeNode(tab, x-1,y, lastValue, xTarget, yTarget);
    initializeNode(tab, x+1,y, lastValue, xTarget, yTarget);
    initializeNode(tab, x,y-1, lastValue, xTarget, yTarget);
    initializeNode(tab, x,y+1, lastValue, xTarget, yTarget);
}

Node *findMin(Node **node)
{
      int currentMin = 999999 ;
    Node *result = NULL;

    for (  int i = 0; i < globalCurrent->numberLines; i++)
    {
        for (  int j = 0; j < strlen(globalCurrent->map[i]); j++)
        {
            // printf("%u_%u_%u_%d_%d \n", node[i][j].gCost, node[i][j].hCost, node[i][j].total_cost, (int)node[i][j].isOpen, (int)node[i][j].type);
            if ((node[i][j].total_cost < currentMin) && (node[i][j].total_cost > 0) && (node[i][j].isOpen == 1) && (node[i][j].type == TRAVERSABLE))
            {
                printf("JE SUIS RENTREEEE\n");
                currentMin = node[i][j].total_cost;
                result = &node[i][j];
                
            }
        }
    }
    result->isOpen = 0;
    printf("IL A OPEEEN\n");
    return result;
}

void pathfinding(Node **graph,   int xStart,   int yStart,   int xTarget,   int yTarget)
{

    Node *currentNode = &graph[yStart][xStart];

    currentNode->hCost = sqrt((xStart - xTarget) * (xStart - xTarget) + (yStart - yTarget) * (yStart - yTarget));
    currentNode->isOpen = 0;
    currentNode->total_cost = 2;
    currentNode->gCost = 1;
    Node *nextMin = &graph[xStart][yStart];
    // while (currentNode != &graph[xTarget][yTarget])
    for (int i = 0; i < 50; i++)
    {

        initializeSurrounding(graph, nextMin->x,nextMin->y,nextMin->gCost, xTarget, yTarget);

        nextMin = findMin(graph);
    }
}
