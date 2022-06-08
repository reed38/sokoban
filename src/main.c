#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"
#include "pathfinding.h"

int main(void)
{
    char *levelFile = "data/level/levels.lvl";
    readLevelsFile(levelFile);
    globalCurrent = levelsNode;
    initLevel(globalCurrent);
   // Node **graph = pathfinding (globalCurrent,5,1,6,1);
   Node **graph=convertToNode(globalCurrent);
    printfGraph(graph,globalCurrent);
    
   
   for (int i = 0; i < globalCurrent->numberLines; i++)
    {
        free(graph[i]);
    }
    free(graph);
    // configureTerminal();
    // interactionLoop();
    return 0;
    
}
