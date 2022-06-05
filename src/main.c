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
    int playerX=levelsNode->playerX;
    int playerY=levelsNode->playerY;
    for(int i = 0; i != numberLines; i++) 
	    printf("\t\t%s\n", mapBuffer);



}
