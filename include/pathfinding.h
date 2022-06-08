#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__
typedef struct Node
{
    unsigned int gCost; // distance depuis le point de départ
    unsigned int hCost;
    unsigned int total_cost;
    char type;   // TRAVERSABLE, NOTTRAVERSABLE,
    char isOpen; // 0 pour unexplored, 1 pour explored
} Node;

void somebodyOnceToldMe(Level *level, unsigned int xStart, unsigned int yStart, unsigned int xTarget, unsigned int yTarget);
Node **convertToNode(Level *level);
unsigned int maxLength(Level *level);
void printfGraph(Node **node);

#endif


