/**
 * @file testLevelLoader.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme testant l'affichage sur le terminal.
 * 
 */
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

	Level *currentLevel = levelsNode;
    for (int i=0; i<6; i++)
	{
		initLevel(currentLevel);
		printLevel(currentLevel);
		sleep(2);
		currentLevel = currentLevel->nextLevel;
	}
    resetTerminal();
	/*initLevel(levelsNode);
    initLevel(levelsNode->nextLevel);

    for (;;)
    {
		
		printLevel(levelsNode);
        sleep(2);
        //levelsNode->nextLevel->numberMov = 255;
        //levelsNode->nextLevel->numberPush = 1;
        printLevel(levelsNode->nextLevel);
    	sleep(2);
		
        for(int i = 0; i <= 1; i++)
        {
            levelsNode->map[0][0] = '#';
            printLevel(levelsNode);
            sleep(1);

            levelsNode->map[0][0] = ' ';
            printLevel(levelsNode);
            sleep(1);
        }

    }*/
}