#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"
#include "pathfinding.h"
#define TRAVERSABLE 0
#define NOTTRAVERSABLE 1
unsigned int maxLength(Level *level);
static void initializeSurrounding(Node **node, Level *level, unsigned int x, unsigned int y, int xTarget, int yTarget);
static void initializeNode(Node **node, Level *level, unsigned int x, unsigned int y, unsigned int lastValue, int xTarget, int yTarget);
unsigned int *findMin(Node **node);
static char doesExist(Node **node, Level *level, unsigned int x, unsigned int y);
// distance verticale et horizontale de 10
// distance diagonale de 14
/**
 * @brief prend un level en paramètre et renvoi la longueur max des ses lignes
 *
 * @param level
 * @return unsigned int
 */
unsigned int maxLength(Level *level)
{
    int maxLength = 0;
    unsigned int a;
    for (unsigned int i = 0; i < level->numberLines; i++)
    {
        if ((a = strlen(level->map[i])) > maxLength)
            maxLength = a;
    }
    return maxLength;
}

/**
 * @brief prend en entrée un taableau 2D de chars et renvoi un tableau de struct de Node
 *
 * @param level struct Level
 * @return retourne un double pointeur de Node
 */
Node **convertToNode(Level *level) // permet de convertir un niveau en tableau 2 D de structure de type Node, s'apparentant à un graph
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

/**
 * @brief permet d'afficher le champs type d'un double pointeur de node pour vérrifier que la conversion en node s'est biien passée
 *
 * @param double pointeur de Node
 */
void printfGraph(Node **node, Level *level)

{
    for (unsigned int i = 0; i < level->numberLines; i++)
    {
        printf("\n");
        for (unsigned int j = 0; j < strlen(level->map[i]); j++)
        {
            printf("%u_%u_%u_%d_%d ", node[i][j].gCost, node[i][j].hCost, node[i][j].total_cost, (int)node[i][j].isOpen, (int)node[i][j].type);
        }
    }
}

static char doesExist(Node **node, Level *level, unsigned int x, unsigned int y)
{
    /*
    printf("1:%ld ", strlen(globalCurrent->map[y]));
    printf("2:%d", globalCurrent->numberLines);*/

    if (y < level->numberLines && x < strlen(level->map[y]) && x >= 0 && y >= 0)
        return 1;
    else
        return 0;
}
static void initializeNode(Node **node, Level *level, unsigned int x, unsigned int y, unsigned int lastValue, int xTarget, int yTarget) // position 0 pour diagonale 1 autrement
{
    if (doesExist(node, level, x, y))
    {
        if (node[y][x].isOpen == 1 && node[y][x].type == TRAVERSABLE)
        {
            node[y][x].hCost = sqrt((x - xTarget) * (x - xTarget) + (y - yTarget) * (y - yTarget));

            node[y][x].gCost += 1;

            node[y][x].total_cost = node[y][x].hCost + node[y][x].gCost;
        }
    }
}

static void initializeSurrounding(Node **node, Level *level, unsigned int x, unsigned int y, int xTarget, int yTarget)
{

    initializeNode(node, level, x, y + 1, node[y][x].gCost, xTarget, yTarget);
    initializeNode(node, level, x, y - 1, node[y][x].gCost, xTarget, yTarget);
    initializeNode(node, level, x - 1, y, node[y][x].gCost, xTarget, yTarget);
    initializeNode(node, level, x + 1, y, node[y][x].gCost, xTarget, yTarget);
}

unsigned int *findMin(Node **node)
{
    unsigned int *result = malloc(2 * sizeof(unsigned int)); // case 1:x, case 2:y
    unsigned int currentMin = 65530;
    for (int i = 1; i < globalCurrent->numberLines; i++)
    {
        for (int j = 1; j < strlen(globalCurrent->map[i]); j++)
        {
            if (node[i][j].total_cost < currentMin && node[i][j].isOpen == 1 && node[i][j].type == TRAVERSABLE)
            {
                currentMin = node[i][j].total_cost;
                result[0] = i;
                result[1] = j;
            }
        }
    }
    node[result[0]][result[1]].isOpen = 0;

    return result;
}

Node **pathfinding(Level *level, unsigned int xStart, unsigned int yStart, unsigned int xTarget, unsigned int yTarget)
{
    Node **graph = convertToNode(level);
    Node *currentNode = &graph[xStart][yStart];

    unsigned int *nodeCoordinates = malloc(sizeof(unsigned int) * 2);
    nodeCoordinates[0] = 0;
    nodeCoordinates[1] = 0;
    currentNode->hCost = sqrt((xStart - xTarget) * (xStart - xTarget) + (yStart - yTarget) * (yStart - yTarget));
    currentNode->isOpen = 0;
    currentNode->gCost = 0;
    while (currentNode != &graph[xTarget][yTarget])
    {
        initializeSurrounding(graph, nodeCoordinates[0], nodeCoordinates[1], xTarget, yTarget);
        nodeCoordinates = findMin(graph);
    }
    return graph;
}
/*
// char **
// on commence par remplacer les caisses pleines et vides par des murs
char isDirectPathBlocked(Level *level, unsigned int x, unsigned int y) // test si la route directe est libre
{
    char **tab = level->map;
    int *distToTarget = targetDistance;
    if (x < level->playerY)
    {
        for (int i = x; i < level->playerY; i++)
        {
            if (tab[y][i] == WALL)
                return 0;
        }
    }
    if (x > level->playerY)
    {
        for (int i = level->playerY; i < x; i++)
        {
            if (tab[y][i] == WALL)
                return 0;
        }
    }
    if (y < level->playerX)
    {
        for (int i = y; i < level->playerX; i++)
        {
            if (tab[i][x] == WALL)
                return 0;
        }
    }
    if (y > level->playerY)
    {
        for (int i = level->playerX; i < x; i++)
        {
            if (tab[i][x] == WALL)
                return 0;
        }
    }unsigned int* result=malloc(2*sizeof(unsigned int));

void chuisperdu(Level *level, unsigned int x, unsigned int y)
{

    int *distanceToTarget = targetDistance(level, x, y);
    switch (distanceToTarget[0])
    {
    }
}
// A* algorithm
*/