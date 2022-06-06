#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keys.h"
#include "movements.h"
#include "graphics.h"
#include "levelLoader.h"


int main(void)
{
    char *levelFile="level.lvl";
    readLevelsFile(levelFile);
    char **mapBuffer=levelsNode->map;
    int numberLines=levelsNode->numberLines;
    determinePlayerCoord(mapBuffer);
    unsigned int playerX=levelsNode->playerX;
    unsigned int playerY=levelsNode->playerY;

    configureTerminal();
    terminalRefresh(mapBuffer,numberLines);
    
    while(1)
    {
        move(&playerY,&playerX,mapBuffer);
        terminalRefresh(mapBuffer,numberLines);
    }



}
