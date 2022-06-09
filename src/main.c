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
    char *levelFile = "../data/level/levels.lvl";
    readLevelsFile(levelFile);
    globalCurrent = levelsNode;
    globalCurrent=globalCurrent->nextLevel;
    initLevel(globalCurrent);
    printLevel(globalCurrent);
   Node **graph=convertToNode(globalCurrent);
    printfGraph(graph,globalCurrent);
  
       pathfinding (graph,1,1,9,1);
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
