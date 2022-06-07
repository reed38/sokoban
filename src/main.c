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
    globalCurrent=levelsNode;
    initLevel(globalCurrent);
    
       
    configureTerminal();
    interactionLoop();
    
    
    
    
        
        
    
    }
    





