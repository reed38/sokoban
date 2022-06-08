/**
 * @file testMovements.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme de test de la gestion des mouvements du joueur.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"

void testMovements(void)
{
    char *levelFile = "data/level/levels.lvl";
    char *saveFile = "data/save/save.lvl";
    readLevelsFile(levelFile);
    globalCurrentLevel=levelsNode;
    initLevel(globalCurrentLevel, 0);
    
    configureTerminal();
    interactionLoop(saveFile);
}