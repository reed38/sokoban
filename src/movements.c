#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "keys.h"
#include "movements.h"

static void goRight(unsigned int *x, unsigned int *y, char **currentMap);
static void goLeft(unsigned int *x, unsigned int *y, char **currentMap);
static void goUp(unsigned int *x, unsigned int *y, char **currentMap);
static void goDown(unsigned int *x, unsigned int *y, char **currentMap);


/**
 * @brief détecte l'input du joueur, puis modifie les coordonnées du joueur et
 * l'état de la map en conséquence
 * 
 * @param x coordonnée x du joueur
 * @param y coordonnée y du joueur
 * @param currentMap map modifiée par les actions du joueur
 */
void move(unsigned int *x, unsigned int *y, char **currentMap)
{
    enum Keys  order=getInput();
    switch (order)
    {
        case RIGHT:
            goRight(x,y,currentMap);
            break;
        case LEFT:
            goLeft(x,y,currentMap);
            break;
        case DOWN:
            goDown(x,y,currentMap);
            break;
        case UP:
            goUp(x,y,currentMap);
            break;
        default:
            move(x,y,currentMap);
    }

}


//rappel: rajouter le cas target
/**
 * @brief appellée par move(), permet de se dépacer à droite
 * 
 * @param x  coordonnée x joueur
 * @param y coordonnée y joueur
 * @param currentMap map modifiée par les actions du joueur
 */
static void goRight(unsigned int *x, unsigned int *y, char **currentMap)
{
    if(currentMap[*x][*y]==OVERTARGET)
    {
        if (currentMap[(*x)+1][*y]==NOTHING)
    {
        currentMap[(*x)+1][*y]=PLAYER;
        currentMap[(*x)][*y]=TARGET;
        *x+=1;
        return;
    }
     if (currentMap[(*x)+1][*y]==TARGET)
    {
        currentMap[(*x)+1][*y]=OVERTARGET;
        currentMap[(*x)][*y]=TARGET;
        *x+=1;
        return;
    }
    
    else if(currentMap[(*x)+1][*y]==WALL || (currentMap[(*x)+1][*y]==BOX && currentMap[(*x)+2][*y]==WALL))
        return ;
    
    else 
        {
            if(currentMap[(*x)+2][*y]==NOTHING)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[(*x)+1][*y]=PLAYER;
            currentMap[(*x)+2][*y]=BOX;
            }
            if(currentMap[(*x)+2][*y]==TARGET)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[(*x)+1][*y]=PLAYER;
            currentMap[(*x)+2][*y]=FULLBOX;
            }
            *x+=1;
        }

    }
    else
    {
     
     if (currentMap[(*x)+1][*y]==NOTHING)
    {
        currentMap[(*x)+1][*y]=PLAYER;
        currentMap[(*x)][*y]=NOTHING;
        *x+=1;
        return;
    }
    if (currentMap[(*x)+1][*y]==TARGET)
    {
        currentMap[(*x)+1][*y]=OVERTARGET;
        currentMap[(*x)][*y]=NOTHING;
        *x+=1;
        return;
    }
    
    else if(currentMap[(*x)+1][*y]==WALL || (currentMap[(*x)+1][*y]==BOX && currentMap[(*x)+2][*y]==WALL))
        return ;
    
    else 
        {
            if(currentMap[(*x)+2][*y]==NOTHING)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[(*x)+1][*y]=PLAYER;
            currentMap[(*x)+2][*y]=BOX;
            }
            if(currentMap[(*x)+2][*y]==TARGET)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[(*x)+1][*y]=PLAYER;
            currentMap[(*x)+2][*y]=FULLBOX;
            }
            *x+=1;
        } 
    }
}
/**
 * @brief appellée par move(), permet de se dépacer à gauche
 * 
 * @param x  coordonnée x joueur
 * @param y coordonnée y joueur
 * @param currentMap map modifiée par les actions du joueur
 */
static void goLeft(unsigned int *x, unsigned int *y, char **currentMap)
{
    if(currentMap[*x][*y]==OVERTARGET)
    {
        if (currentMap[(*x)+1][*y]==NOTHING)
    {
        currentMap[(*x)-1][*y]=PLAYER;
        currentMap[(*x)][*y]=TARGET;
        *x-=1;
        return;
    }
     if (currentMap[(*x)-1][*y]==TARGET)
    {
        currentMap[(*x)-1][*y]=OVERTARGET;
        currentMap[(*x)][*y]=TARGET;
        *x-=1;
        return;
    }
    
    else if(currentMap[(*x)-1][*y]==WALL || (currentMap[(*x)-1][*y]==BOX && currentMap[(*x)-2][*y]==WALL))
        return ;
    
    else 
        {
            if(currentMap[(*x)-2][*y]==NOTHING)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[(*x)-1][*y]=PLAYER;
            currentMap[(*x)-2][*y]=BOX;
            }
            if(currentMap[(*x)-2][*y]==TARGET)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[(*x)-1][*y]=PLAYER;
            currentMap[(*x)-2][*y]=FULLBOX;
            }
            *x-=1;
        }

    }
    else
    {
     
     if (currentMap[(*x)-1][*y]==NOTHING)
    {
        currentMap[(*x)-1][*y]=PLAYER;
        currentMap[(*x)][*y]=NOTHING;
        *x-=1;
        return;
    }
    if (currentMap[(*x)-1][*y]==TARGET)
    {
        currentMap[(*x)-1][*y]=OVERTARGET;
        currentMap[(*x)][*y]=NOTHING;
        *x-=1;
        return;
    }
    
    else if(currentMap[(*x)-1][*y]==WALL || (currentMap[(*x)+1][*y]==BOX && currentMap[(*x)-2][*y]==WALL))
        return ;
    
    else 
        {
            if(currentMap[(*x)-2][*y]==NOTHING)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[(*x)-1][*y]=PLAYER;
            currentMap[(*x)-2][*y]=BOX;
            }
            if(currentMap[(*x)-2][*y]==TARGET)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[(*x)-1][*y]=PLAYER;
            currentMap[(*x)-2][*y]=FULLBOX;
            }
            *x-=1;
        } 
    }
}
/**
 * @brief appellée par move(), permet de se dépacer vers le haut
 * 
 * @param x  coordonnée x joueur
 * @param y coordonnée y joueur
 * @param currentMap map modifiée par les actions du joueur
 */
static void goUp(unsigned int *x, unsigned int *y, char **currentMap)
{
    if(currentMap[*x][*y]==OVERTARGET)
    {
        if (currentMap[*x][*(y+1)]==NOTHING)
    {
        currentMap[*x][*(y+1)]=PLAYER;
        currentMap[*x][*y]=TARGET;
        *y+=1;
        return;
    }
     if (currentMap[*x][*(y+1)]==TARGET)
    {
        currentMap[*x][*(y+1)]=OVERTARGET;
        currentMap[*x][*y]=TARGET;
        *y+=1;
        return;
    }
    
    else if(currentMap[*x][*(y+1)]==WALL || (currentMap[*x][*(y+1)]==BOX && currentMap[*x][*(y+2)]==WALL))
        return ;
    
    else 
        {
            if(currentMap[*x][*(y+2)]==NOTHING)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[*x][*(y+1)]=PLAYER;
            currentMap[*x][*(y+2)]=BOX;
            }
            if(currentMap[*x][*(y+2)]==TARGET)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[*x][*(y+1)]=PLAYER;
            currentMap[*x][*(y+2)]=FULLBOX;
            }
            *y+=1;
        }

    }
    else
    {
     
     if (currentMap[*x][*(y+1)]==NOTHING)
    {
        currentMap[*x][*(y+1)]=PLAYER;
        currentMap[(*x)][*y]=NOTHING;
        *y+=1;
        return;
    }
    if (currentMap[*x][*(y+1)]==TARGET)
    {
        currentMap[*x][*(y+1)]=OVERTARGET;
        currentMap[(*x)][*y]=NOTHING;
        *y+=1;
        return;
    }
    
    else if(currentMap[*x][*(y+1)]==WALL || (currentMap[*x][*(y+1)]==BOX && currentMap[*x][*(y+2)]==WALL))
        return ;
    
    else 
        {
            if(currentMap[*x][*(y+2)]==NOTHING)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[*x][*(y+1)]=PLAYER;
            currentMap[*x][*(y+2)]=BOX;
            }
            if(currentMap[*x][*(y+2)]==TARGET)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[*x][*(y+1)]=PLAYER;
            currentMap[*x][*(y+2)]=FULLBOX;
            }
            *y+=1;
        } 
    }
}
/**
 * @brief appellée par move(), permet de se dépacer vers le bas
 * 
 * @param x  coordonnée x joueur
 * @param y coordonnée y joueur
 * @param currentMap map modifiée par les actions du joueur
 */
static void goDown(unsigned int *x, unsigned int *y, char **currentMap)
{
     if(currentMap[*x][*y]==OVERTARGET)
    {
        if (currentMap[*x][*(y-1)]==NOTHING)
    {
        currentMap[*x][*(y-1)]=PLAYER;
        currentMap[*x][*y]=TARGET;
        *y-=1;
        return;
    }
     if (currentMap[*x][*(y-1)]==TARGET)
    {
        currentMap[*x][*(y-1)]=OVERTARGET;
        currentMap[*x][*y]=TARGET;
        *y-=1;
        return;
    }
    
    else if(currentMap[*x][*(y-1)]==WALL || (currentMap[*x][*(y-1)]==BOX && currentMap[*x][*(y-2)]==WALL))
        return ;
    
    else 
        {
            if(currentMap[*x][*(y-2)]==NOTHING)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[*x][*(y-1)]=PLAYER;
            currentMap[*x][*(y-2)]=BOX;
            }
            if(currentMap[*x][*(y-2)]==TARGET)
            {
            currentMap[*x][*y]=TARGET;
            currentMap[*x][*(y-1)]=PLAYER;
            currentMap[*x][*(y-2)]=FULLBOX;
            }
            *y-=1;
        }

    }
    else
    {
     
     if (currentMap[*x][*(y-1)]==NOTHING)
    {
        currentMap[*x][*(y-1)]=PLAYER;
        currentMap[(*x)][*y]=NOTHING;
        *y-=1;
        return;
    }
    if (currentMap[*x][*(y-1)]==TARGET)
    {
        currentMap[*x][*(y-1)]=OVERTARGET;
        currentMap[(*x)][*y]=NOTHING;
        *y-=1;
        return;
    }
    
    else if(currentMap[*x][*(y-1)]==WALL || (currentMap[*x][*(y-1)]==BOX && currentMap[*x][*(y-2)]==WALL))
        return ;
    
    else 
        {
            if(currentMap[*x][*(y-2)]==NOTHING)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[*x][*(y-1)]=PLAYER;
            currentMap[*x][*(y-2)]=BOX;
            }
            if(currentMap[*x][*(y-2)]==TARGET)
            {
            currentMap[*x][*y]=NOTHING;
            currentMap[*x][*(y-1)]=PLAYER;
            currentMap[*x][*(y-2)]=FULLBOX;
            }
            *y-=1;
        } 
    }
}