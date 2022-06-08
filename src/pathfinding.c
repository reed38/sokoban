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

unsigned int wallDistance(int direction, Level *level);
unsigned int maxLength(Level *level);
static Node *returneNode(Node **node, unsigned int x, unsigned int y, unsigned int xMax, unsigned int yMax);
static void defineSurrounding(Node **tab, unsigned int xNode, unsigned int yNode, unsigned int xTarget, unsigned int yTarget, unsigned int xMax, unsigned int yMax);
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
void printfGraph(Node **node)
{
    for (unsigned int i = 0; i < globalCurrent->numberLines; i++)
    {
        printf("\n");
        for (unsigned int j = 0; j < strlen(globalCurrent->map[i]); j++)
        {
            printf("%u_%u_%u_%d_%d ", node[i][j].gCost, node[i][j].hCost, node[i][j].total_cost, (int)node[i][j].isOpen,(int) node[i][j].type);
        }
    }
}
/**
 * @brief permet de vérrifier si un point se trouve bien dans le tableau
 *
 * @param node double pointeur Node contenant le tableau 2D de Node
 * @param x coordonnée x du point
 * @param y coordonnée y du point
 * @param xMax coordonnée max x du tableau 2D de node
 * @param yMax coordonnée max y du tableau 2D de node
 * @return retourne un pointeur de node sur node[x][y] si le point est dans le tableau NULL sinon
 */
static Node *returneNode(Node **node, unsigned int x, unsigned int y, unsigned int xMax, unsigned int yMax) // retourne le Node si celui ci existe dans la liste 2 D de Node sinon NULL
{
    if (x < xMax && y < yMax && x >= 0 && y >= 0)
        return &node[x][y];
    else
        return NULL;
}
/**
 * @brief permet d'exporer et initialiser les 8 nodes voisins de la node dont les coordonnées sont saisits
 *
 * @param tab double pointeur de C
 * @param xNode coordonnée x de la node centrale
 * @param yNode coordonnée y de la node centrale
 * @param xTarget coordonnée x de la cible
 * @param yTarget coordonnée y de la cible
 * @param xMax coordonnée max x du tableau 2D de node
 * @param yMax coordonnée max y du tableau 2D de node
 * @return nada senor
 */
static void defineSurrounding(Node **tab, unsigned int xNode, unsigned int yNode, unsigned int xTarget, unsigned int yTarget, unsigned int xMax, unsigned int yMax)
{
    Node **surrounding = malloc(8 * sizeof(Node *));
    surrounding[0] = returneNode(tab, xNode + 1, yNode + 1, xMax, yMax);
    surrounding[1] = returneNode(tab, xNode + 1, yNode - 1, xMax, yMax);
    surrounding[2] = returneNode(tab, xNode - 1, yNode - 1, xMax, yMax);
    surrounding[3] = returneNode(tab, xNode - 1, yNode + 1, xMax, yMax);
    surrounding[4] = returneNode(tab, xNode - 1, yNode, xMax, yMax);
    surrounding[5] = returneNode(tab, xNode + 1, yNode, xMax, yMax);
    surrounding[6] = returneNode(tab, xNode, yNode + 1, xMax, yMax);
    surrounding[7] = returneNode(tab, xNode, yNode - 1, xMax, yMax);

    for (int i = 0; i < 7; i++)
    {
        if (surrounding[i] != NULL && surrounding[i]->type == TRAVERSABLE && surrounding[i]->isOpen == 1) // si le node est traversable et n'est pas Closed
        {

            if (i < 3) // les 4 premières case correspondent aux nodes les plus éloignés du centre
            {
                surrounding[i]->gCost = (tab[xNode][yNode].gCost + 14);
            }
            else if (i < 7)
            {
                surrounding[i]->gCost = tab[xNode][yNode].gCost + 10;
            }
            surrounding[i]->hCost = sqrt((xNode - xTarget) * (xNode - xTarget) + (yNode - yTarget) * (yNode - yTarget)); // distance à l'arrivée
            surrounding[i]->total_cost = surrounding[i]->hCost + surrounding[i]->gCost;
        }
    }
    free(surrounding);
}

unsigned int *findMin(Node **node, unsigned int xMax, unsigned int yMax)
{
    unsigned int currentMin = node[0][0].total_cost;
    unsigned int *result = malloc(2 * sizeof(unsigned int)); // case 1:x, case 2:y

    for (int i = 1; i < xMax; i++)
    {
        for (int j = 1; j < yMax; j++)
        {
            if (node[i][j].total_cost < currentMin &&node[i][j].isOpen==1 && node[i][j].type==TRAVERSABLE)
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
        defineSurrounding(graph, nodeCoordinates[0], nodeCoordinates[1], xTarget, yTarget, strlen(level->map[nodeCoordinates[0]]), level->numberLines);
        nodeCoordinates = findMin(graph, strlen(level->map[nodeCoordinates[0]]), level->numberLines);
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