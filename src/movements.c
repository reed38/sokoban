#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "keys.h"
#include "movements.h"


Level *globalCurrent;

static void goRight();
static void goLeft();
static void goUp();
static void goDown();

/**
 * @brief détecte l'input du joueur, puis modifie les coordonnées du joueur et
 * l'état de la map en conséquence
 *
 * @param x coordonnée x du joueur
 * @param y coordonnée y du joueur
 * @param currentMap map modifiée par les actions du joueur
 */
void move(int command)
{
    // todo: à inverser
    
    
    switch (command)
    {
    case RIGHT:
        goRight();
        break;
    case LEFT:
        goLeft();
        break;
    case DOWN:
        goDown();
        break;
    case UP:
        goUp();
        break;
    default:
        break;
    }
}

// tab[y][x], y ordonnée x abscisse
// max abscisse: strlen
// max ordonnée: numbreLine char **currentMap = globalCurrent->map; 
   /*
I-sur target
-devant vide 1
-devant target 1
-devant box espace derrière 2
-devant box pas espace derrière 1
-devant box target derrière 2
II-pas sur target
-devant vide
-devant target
-devant box espace derrière
-devant box pas espace derrière
-devant box target derrière

*/


/**
 * @brief permet de déplacer le personnage à droite et d'intéragir aves les objets se trouvant à droite
 * @args: void, Goright intéragit avec la struct Level globalCurrent contenant la map, les coordnnées du personnage ect
 */

static void goRight()
{
    char **currentMap = globalCurrent->map; 
    unsigned int *y=&globalCurrent->playerX;
    unsigned int *x=&globalCurrent->playerY;
    char nextCase=(currentMap[*y][*x]==OVERTARGET)?TARGET:NOTHING; //on différencie le cas où le personnage est sur une target et celui poù il est sur rien





        if (currentMap[*y][*x + 1] == NOTHING)
        {
            currentMap[*y][*x + 1] = PLAYER;
            currentMap[*y][*x] = nextCase;
            *x += 1;
        }
        else if (currentMap[*y][*x + 1] == TARGET)
        {
            currentMap[*y][*x + 1] = OVERTARGET;
            currentMap[*y][*x] = nextCase;
            *x += 1;
        }
        else if (currentMap[*y][*x + 1] == BOX || currentMap[*y][*x + 1] == FULLBOX)
        {
            if (currentMap[*y][*x + 2] != WALL && currentMap[*y][*x + 2] != BOX && currentMap[*y][*x + 2] != FULLBOX)
            {
                if (currentMap[*y][*x + 2] == NOTHING)
                {
                    if (currentMap[*y][*x + 1] == FULLBOX)
                    {
                        currentMap[*y][*x + 1] = OVERTARGET;
                        currentMap[*y][*x + 2] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *x += 1;
                    }
                    else if (currentMap[*y][*x + 1] == BOX)
                    {
                        currentMap[*y][*x + 1] = PLAYER;
                        currentMap[*y][*x + 2] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *x += 1;
                    }
                }
                else if (currentMap[*y][*x + 2] == TARGET)
                {
                    if (currentMap[*y][*x + 1] == FULLBOX)
                    {
                        currentMap[*y][*x + 1] = OVERTARGET;
                        currentMap[*y][*x + 2] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *x += 1;
                    }
                    else if (currentMap[*y][*x + 1] == BOX)
                    {
                        currentMap[*y][*x + 1] = PLAYER;
                        currentMap[*y][*x + 2] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *x += 1;
                    }
                }
            }
        }
    
}
/**
 * @brief permet de déplacer le personnage à droite et d'intéragir aves les objets se trouvant à gauche
 * @args: void, Goright intéragit avec la struct Level globalCurrent contenant la map, les coordnnées du personnage ect
 */
static void goLeft()
{
 char **currentMap = globalCurrent->map; 
    unsigned int *y=&globalCurrent->playerX;
    unsigned int *x=&globalCurrent->playerY;
    char nextCase=(currentMap[*y][*x]==OVERTARGET)?TARGET:NOTHING;

    

        if (currentMap[*y][*x - 1] == NOTHING)
        {
            currentMap[*y][*x - 1] = PLAYER;
            currentMap[*y][*x] = nextCase;
            *x -= 1;
        }
        else if (currentMap[*y][*x - 1] == TARGET)
        {
            currentMap[*y][*x - 1] = OVERTARGET;
            currentMap[*y][*x] = nextCase;
            *x -= 1;
        }
        else if (currentMap[*y][*x - 1] == BOX || currentMap[*y][*x - 1] == FULLBOX)
        {
            if (currentMap[*y][*x - 2] != WALL && currentMap[*y][*x - 2] != BOX && currentMap[*y][*x - 2] != FULLBOX)
            {
                if (currentMap[*y][*x - 2] == NOTHING)
                {
                    if (currentMap[*y][*x - 1] == FULLBOX)
                    {
                        currentMap[*y][*x - 1] = OVERTARGET;
                        currentMap[*y][*x - 2] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *x -= 1;
                    }
                    else if (currentMap[*y][*x - 1] == BOX)
                    {
                        currentMap[*y][*x - 1] = PLAYER;
                        currentMap[*y][*x - 2] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *x -= 1;
                    }
                }
                else if (currentMap[*y][*x - 2] == TARGET)
                {
                    if (currentMap[*y][*x - 1] == FULLBOX)
                    {
                        currentMap[*y][*x - 1] = OVERTARGET;
                        currentMap[*y][*x - 2] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *x -= 1;
                    }
                    else if (currentMap[*y][*x - 1] == BOX)
                    {
                        currentMap[*y][*x - 1] = PLAYER;
                        currentMap[*y][*x - 2] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *x -= 1;
                    }
                }
            }
        }
    
}
/**
 * @brief permet de déplacer le personnage vers le bas et d'intéragir aves les objets se trouvant en dessous
 * @args: void, Goright intéragit avec la struct Level globalCurrent contenant la map, les coordnnées du personnage ect
 */
static void goDown()
{
    char **currentMap = globalCurrent->map; 
    unsigned int *y=&globalCurrent->playerX;
    unsigned int *x=&globalCurrent->playerY;
    char nextCase=(currentMap[*y][*x]==OVERTARGET)?TARGET:NOTHING;
    
        if (currentMap[*y + 1][*x] == NOTHING)
        {
            currentMap[*y + 1][*x] = PLAYER;
            currentMap[*y][*x] = nextCase;
            *y += 1;
        }
        else if (currentMap[*y + 1][*x] == TARGET)
        {
            currentMap[*y + 1][*x] = OVERTARGET;
            currentMap[*y][*x] = nextCase;
            *y += 1;
        }
        else if (currentMap[*y + 1][*x] == BOX || currentMap[*y + 1][*x] == FULLBOX)
        {
            if (currentMap[*y + 2][*x] != WALL && currentMap[*y + 2][*x] != BOX && currentMap[*y + 2][*x] != FULLBOX)
            {
                if (currentMap[*y + 2][*x] == NOTHING)
                {
                    if (currentMap[*y + 1][*x] == FULLBOX)
                    {
                        currentMap[*y + 1][*x] = OVERTARGET;
                        currentMap[*y + 2][*x] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *y += 1;
                    }
                    else if (currentMap[*y + 1][*x] == BOX)
                    {
                        currentMap[*y + 1][*x] = PLAYER;
                        currentMap[*y + 2][*x] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *y += 1;
                    }
                }
                else if (currentMap[*y + 2][*x] == TARGET)
                {
                    if (currentMap[*y + 1][*x] == FULLBOX)
                    {
                        currentMap[*y + 1][*x] = OVERTARGET;
                        currentMap[*y + 2][*x] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *y += 1;
                    }
                    else if (currentMap[*y + 1][*x] == BOX)
                    {
                        currentMap[*y + 1][*x] = PLAYER;
                        currentMap[*y + 2][*x] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *y += 1;
                    }
                }
            }
        }
    
}
/**
 * @brief permet de déplacer le personnage vers le haut et d'intéragir aves les objets se trouvant a dessus
 * @args: void, Goright intéragit avec la struct Level globalCurrent contenant la map, les coordnnées du personnage ect
 */
static void goUp()
{
   char **currentMap = globalCurrent->map; 
    unsigned int *y=&globalCurrent->playerX;
    unsigned int *x=&globalCurrent->playerY;
    char nextCase=(currentMap[*y][*x]==OVERTARGET)?TARGET:NOTHING;
    
        if (currentMap[*y - 1][*x] == NOTHING)
        {
            currentMap[*y - 1][*x] = PLAYER;
            currentMap[*y][*x] = nextCase;
            *y -= 1;
        }
        else if (currentMap[*y - 1][*x] == TARGET)
        {
            currentMap[*y - 1][*x] = OVERTARGET;
            currentMap[*y][*x] = nextCase;
            *y -= 1;
        }
        else if (currentMap[*y - 1][*x] == BOX || currentMap[*y - 1][*x] == FULLBOX)
        {
            if (currentMap[*y - 2][*x] != WALL && currentMap[*y - 2][*x] != BOX && currentMap[*y - 2][*x] != FULLBOX)
            {
                if (currentMap[*y - 2][*x] == NOTHING)
                {
                    if (currentMap[*y - 1][*x] == FULLBOX)
                    {
                        currentMap[*y - 1][*x] = OVERTARGET;
                        currentMap[*y - 2][*x] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *y -= 1;
                    }
                    else if (currentMap[*y - 1][*x] == BOX)
                    {
                        currentMap[*y - 1][*x] = PLAYER;
                        currentMap[*y - 2][*x] = BOX;
                        currentMap[*y][*x] = nextCase;
                        *y -= 1;
                    }
                }
                else if (currentMap[*y - 2][*x] == TARGET)
                {
                    if (currentMap[*y - 1][*x] == FULLBOX)
                    {
                        currentMap[*y - 1][*x] = OVERTARGET;
                        currentMap[*y - 2][*x] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *y -= 1;
                    }
                    else if (currentMap[*y - 1][*x] == BOX)
                    {
                        currentMap[*y - 1][*x] = PLAYER;
                        currentMap[*y - 2][*x] = FULLBOX;
                        currentMap[*y][*x] = nextCase;
                        *y -= 1;
                    }
                }
            }
        }
    
}
