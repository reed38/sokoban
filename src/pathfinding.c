#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"
#define TRAVERSABLE 0
#define NOTTRAVERSABLE 1

unsigned int wallDistance(int direction, Level *level);
convertBoxToWall(Level *level);
char isDirectPathBlocked(Level *level, unsigned int x, unsigned int y);

typedef struct Node
{
    unsigned int g_cost; // distance depuis le point de départ
    unsigned int h_cost;
    unsigned int total_cost;
    char type;   // TRAVERSABLE, NOTTRAVERSABLE,
    char isOpen; // 0 pour unexplored, 1 pour explored
} Node;
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
        if (a = (strlen(level->map[i])) > maxLength)
            maxLength = a;
    }
    return maxLength;
}

Node **convertToNode(Level *level) // permet de convertir un niveau en tableau 2 D de structure de type Node, s'apparentant à un graph
{
    char **map = level->map;
    Node **tabNode = malloc(sizeof(Node) * level->numberLines * maxLength(level));
    for (int i = 0; i < level->numberLines; i++)
    {
        for (int j = 0; j < strlen(map[i]); j++)
        {
            tabNode[i][j].isOpen = 1;
            if (map[i][j] == BOX && map[i][j] == WALL && map[i][j] == FULLBOX)
            {
                tabNode[i][j].type = NOTTRAVERSABLE;
            }
            else
            {
                tabNode[i][j].type = TRAVERSABLE;
            }
        }
    }
}

Node *returneNode(Node *node, unsigned int x, unsigned int y, unsigned int xMax, unsigned int yMax) // retourne le Node si celui ci existe dans la liste 2 D de Node sinon NULL
{
    if (x < xMax && y < yMax && x >= 0 && y >= 0)
        return node;
    else
        return NULL;
}

void defineSurrounding(Node **tab, unsigned int xNode, unsigned int yNode, unsigned int xTarget, unsigned int yTarget, unsigned int xMax, unsigned int yMax)
{
    Node surrounding[8] = {tab[xNode - 1][yNode - 1], tab[xNode + 1][yNode - 1], tab[xNode + 1][yNode + 1], tab[xNode - 1][yNode + 1], tab[xNode][yNode - 1], tab[xNode + 1][yNode], tab[x - 1][y], tab[xNode][yNode + 1]};
    for (int i = 0; i < 7; i++)
    {
        if (surrounding[i].type == TRAVERSABLE && surrounding[i].isOpen == 1) // si le node est traverable et n'est pas Closed
        {

            if (i < 3) // les 4 premières case correspondent aux nodes les plus éloignés du centre
            {
                surrounding[i].g_cost = tab[xNode][y].g_cost + 14;
            }
            else if (i < 7)
            {
                surrounding[i].g_cost = tab[xNode][y].g_cost + 10;
            }
            surrounding[i].h_cost = sqrt((xNode - xTarget) * (xNode - xTarget) + (yNode - yTarget) * (yNode - yTarget)); // distance à l'arrivée
            surrounding[i].total_cost = surrounding[i].h_cost + surrounding[i].g_cost;
        }
    }
}

unsigned int *findMin(Node **node, unsigned int xMax, unsigned int yMax)
{
    unsigned int currentMin = node[0][0].total_cost;
    unsigned int *result = malloc(2 * sizeof(unsigned int)); // case 1:x, case 2:y

    for (int i = 1; i < xMax; i++)
    {
        for (int j = 1; j < yMax; j++)
        {
            if (node[i][j].total_cost < currentMin)
            {
                currentMin = node[i][j].total_cost;
                result[0] = i;
                result[1] = j;
            }
        }
    }
    return result;
}

void somebodyOnceToldMe(Level *level, unsigned int xStart, unsigned int yStart, unsigned int xTarget, unsigned int yTarget)
{
    Node **graph = convertToNode(level);
    Node currentNode=graph[xStart][yStart];
    currentNode.h_cost=sqrt((xStart-xTarget)*(xStart-xTarget)+(yStart-yTarget)*(yStart-yTarget));
    currentNode.isOpen=0;
    currentNode.g_cost=0;
    while(&currentNode!=&graph[xTarget][yTarget])
    {
        
    }

    while
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