#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#define UNSIGNEDMAX   999999

typedef struct Node
{
      int x;
      int y;
      int gCost; // distance depuis le point de départ
      int hCost;
      int total_cost;
    char type;   // 1 TRAVERSABLE, 0 NOTTRAVERSABLE, 
    char isOpen; // 0 pour unexplored, 1 pour explored
} Node;
void pathfinding(Node **graph,   int xStart,   int yStart,   int xTarget,   int yTarget);
Node **convertToNode(Level *level);
  int maxLength(Level *level);
void printfGraph(Node **node,Level *level);

#endif


