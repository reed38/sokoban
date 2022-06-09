#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__


typedef struct Node
{
      int x;
      int y;
      int gCost;
      int hCost;
      int fCost; // distance depuis le point de départ
      char isOpen; // 0 pour undefined ,1 pour open, 2 pour closed; 3  pour à ignorer( intraversables),  
} Node;
void pathfinding(Node **graph,   int xStart,   int yStart,   int xTarget,   int yTarget);
Node **convertToNode(Level *level);
  int maxLength(Level *level);
void printfGraph(Node **node,Level *level);

#endif


