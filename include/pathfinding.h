/*
 * IMPLEMENTATION DE L'ALGORITHME A*
 * NE FONCTIONNE PAS
 * NON INTEGRE DANS LE JEU
 */
#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "levelLoader.h"

/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/

typedef struct Node
{
      int x;
      int y;
      int gCost;
      int hCost;
      int fCost; // distance depuis le point de départ
      char isOpen; // 0 pour undefined ,1 pour open, 2 pour closed; 3 pour à ignorer (intraversable)
} Node;


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

extern void pathfinding(Node **graph,   int xStart,   int yStart,   int xTarget,   int yTarget);
extern Node **convertToNode(Level *level);
extern int maxLength(Level *level);
extern void printfGraph(Node **node,Level *level);
extern void testPathfinding(void);

#endif


