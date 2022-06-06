#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"
#include "levelLoader.h"


void testGraphics(void)
{   
    readLevelsFile("data/level/levels2.lvl");

    configureTerminal();
    if(levelsNode == NULL || levelsNode->nextLevel == NULL)
    {
        fprintf(stderr, "Besoin d'au moins 2 niveaux pour effectuer le test graphique...\n");
        return;
    }

    for (;;)
    {
        printLevel(levelsNode);
        sleep(2);
        
        printLevel(levelsNode->nextLevel);
        sleep(2);
    }
}