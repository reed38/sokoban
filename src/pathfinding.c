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
static void initializeSurrounding(Node **tab, Node *node, int xTarget, int yTarget);
static void initializeNode(Node **tab, Node *node ,unsigned int lastValue, unsigned int xTarget, unsigned int yTarget);
Node *findMin( Node **node);
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
            tabNode[i][j].x=j;
            tabNode[i][j].y=i;
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
            printf("%d ", node[i][j].isOpen);
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

static void initializeNode(Node **tab,Node* node, unsigned int lastValue, unsigned int xTarget, unsigned int yTarget) // position 0 pour diagonale 1 autrement
{
    if (doesExist(node->x, node->y))
    {
        if (node->isOpen == 1 && node->type == TRAVERSABLE)
        {
            node->hCost =(int) sqrt((node->x - xTarget) * (node->x - xTarget) + (node->y - yTarget) * (node->y - yTarget));

            node->gCost=lastValue+1;

            node->total_cost = node->hCost + node->gCost;
        }
    }
}

static void initializeSurrounding(Node **tab, Node *node, int xTarget, int yTarget)
{

    initializeNode(tab, node, node->gCost, xTarget, yTarget);
    initializeNode(tab, node ,node->gCost, xTarget, yTarget);
    initializeNode(tab,node, node->gCost, xTarget, yTarget);
    initializeNode(tab, node, node->gCost, xTarget, yTarget);
}

Node *findMin( Node **node)
{
    unsigned int currentMin = MAXUNSIGNED;
    Node *result;
    
    for (unsigned int i = 0; i < globalCurrent->numberLines; i++)
    {
        for (unsigned int j = 0; j < strlen(globalCurrent->map[i]); j++)
        {
            if ((node[i][j].total_cost < currentMin) && (node[i][j].total_cost > 0) && (node[i][j].isOpen == 1) && (node[i][j].type == TRAVERSABLE))
            {
                currentMin = node[i][j].total_cost;
                result=&node[i][j];
            }
        }
    }
        result->isOpen = 0;

    return result;
}

void pathfinding(Node **graph, unsigned int xStart, unsigned int yStart, unsigned int xTarget, unsigned int yTarget)
{

    Node *currentNode = &graph[yStart][xStart];

   
    currentNode->hCost = sqrt((xStart - xTarget) * (xStart - xTarget) + (yStart - yTarget) * (yStart - yTarget));
    currentNode->isOpen = 0;
    currentNode->total_cost = 2;
    Node *nextMin=& graph[xStart][yStart];
    // while (currentNode != &graph[xTarget][yTarget])
    for (int i = 0; i < 50; i++)
    {           
        initializeSurrounding(graph,nextMin,xTarget,yTarget);
        nextMin = findMin( graph);

        
    }
}
