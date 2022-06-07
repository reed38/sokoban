#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"

int main(void)
{
    char *levelFile="data/level/levels.lvl";
    readLevelsFile(levelFile);
    Level *levelPtr=levelsNode;
    char **mapBuffer=levelPtr->map;
    determinePlayerCoord(levelPtr);
    unsigned int playerX=levelPtr->playerY;
    unsigned int playerY=levelPtr->playerX;
   
    terminalRefresh(mapBuffer,levelPtr->numberLines);
    
   configureTerminal();
    while(1)
    {
        terminalRefresh(mapBuffer,levelPtr->numberLines);
        move(&playerX,&playerY,levelPtr->map);
        printf(" x:%d y:%d\n",playerX,playerY);

    }
    
    
    
    
        
        
    
    }
    





