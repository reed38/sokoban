#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "keys.h"
#include "movements.h"

static void goRight(unsigned int *y, unsigned int *x , char **currentMap);
static void goLeft(unsigned int *y, unsigned int *x,   char **currentMap);
static void goUp(unsigned int *y, unsigned int *x,  char **currentMap);
static void goDown(unsigned int *y, unsigned int *x , char **currentMap);


/**
 * @brief détecte l'input du joueur, puis modifie les coordonnées du joueur et
 * l'état de la map en conséquence
 * 
 * @param x coordonnée x du joueur
 * @param y coordonnée y du joueur
 * @param currentMap map modifiée par les actions du joueur
 */
void move(unsigned int *y, unsigned int *x, char **currentMap)
{
    enum Keys  order=getInput();
    switch (order)
    {
        case RIGHT:
            goRight(x,y, currentMap);
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

//tab[y][x], y ordonnée x abscisse
//max abscisse: strlen
//max ordonnée: numbreLine
 /*cas à faire:
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

char next(char current)
{
    
    if (current==NOTHING)
        return (NOTHING);
    else 
        return (TARGET);
}


static void goRight(unsigned int *y, unsigned int *x , char **currentMap)
{
    char nextValue;
    char current=currentMap[*x][*y];
    if (current==' ')
        nextValue=' ';
    else 
        nextValue='.';
   
    
       
        
        
       
            if(currentMap[*y][*x+1]==NOTHING)
            {
                currentMap[*y][*x+1]=PLAYER;
                currentMap[*y][*x]=nextValue;
                *x+=1;
                
            }
            else  if(currentMap[*y][*x+1]==TARGET)
            {
                currentMap[*y][*x+1]=OVERTARGET;
                currentMap[*y][*x]=nextValue;
                *x+=1;
            }
            else if(currentMap[*y][*x+1]==BOX || currentMap[*y][*x+1]==FULLBOX)
            {
                if ( currentMap[*y][*x+2]!=WALL && currentMap[*y][*x+2]!=BOX && currentMap[*y][*x+2]!=FULLBOX)
                {
                    if(currentMap[*y][*x+2]==NOTHING)
                    {
                        if(currentMap[*y][*x+1]==FULLBOX)
                        {
                            currentMap[*y][*x+1]=OVERTARGET;
                            currentMap[*y][*x+2]=BOX;
                            currentMap[*y][*x]=nextValue;
                            *x+=1;
                        }
                        else if(currentMap[*y][*x+1]==BOX)
                        {   currentMap[*y][*x+1]=PLAYER;
                            currentMap[*y][*x+2]=BOX;
                            currentMap[*y][*x]=nextValue;
                            *x+=1;

                        }
                        
                    }
                    else if(currentMap[*y][*x+2]==TARGET)
                    {
                        if(currentMap[*y][*x+1]==FULLBOX)
                        {
                            currentMap[*y][*x+1]=OVERTARGET;
                            currentMap[*y][*x+2]=FULLBOX;
                            currentMap[*y][*x]=nextValue;
                            *x+=1;
                        }
                        else if(currentMap[*y][*x+1]==BOX)
                        {
                            currentMap[*y][*x+1]=PLAYER;
                            currentMap[*y][*x+2]=FULLBOX;
                            currentMap[*y][*x]=nextValue;
                            *x+=1;  
                        }
                    }
                 }
            }
        
    
}

static void goLeft(unsigned int *y, unsigned int *x , char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET)
    {
       
        
       
            if(currentMap[*y][*x-1]==NOTHING)
            {
                currentMap[*y][*x-1]=PLAYER;
                currentMap[*y][*x]=TARGET;
                *x-=1;
                
            }
            else  if(currentMap[*y][*x-1]==TARGET)
            {
                currentMap[*y][*x-1]=OVERTARGET;
                currentMap[*y][*x]=TARGET;
                *x-=1;
            }
            else if(currentMap[*y][*x-1]==BOX || currentMap[*y][*x-1]==FULLBOX)
            {
                if ( currentMap[*y][*x-2]!=WALL && currentMap[*y][*x-2]!=BOX && currentMap[*y][*x-2]!=FULLBOX)
                {
                    if(currentMap[*y][*x-2]==NOTHING)
                    {
                        if(currentMap[*y][*x-1]==FULLBOX)
                        {
                            currentMap[*y][*x-1]=OVERTARGET;
                            currentMap[*y][*x-2]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *x-=1;
                        }
                        else if(currentMap[*y][*x-1]==BOX)
                        {   currentMap[*y][*x-1]=PLAYER;
                            currentMap[*y][*x-2]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *x-=1;

                        }
                        
                    }
                    else if(currentMap[*y][*x-2]==TARGET)
                    {
                        if(currentMap[*y][*x-1]==FULLBOX)
                        {
                            currentMap[*y][*x-1]=OVERTARGET;
                            currentMap[*y][*x-2]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *x-=1;
                        }
                        else if(currentMap[*y][*x-1]==BOX)
                        {
                            currentMap[*y][*x-1]=PLAYER;
                            currentMap[*y][*x-2]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *x-=1;  
                        }
                    }
                 }
            }
        
    }
    else
    {
       
            if(currentMap[*y][*x-1]==NOTHING)
            {
                currentMap[*y][*x-1]=PLAYER;
                currentMap[*y][*x]=NOTHING;
                *x-=1;
                
            }
            else  if(currentMap[*y][*x-1]==TARGET)
            {
                currentMap[*y][*x-1]=OVERTARGET;
                currentMap[*y][*x]=NOTHING;
                *x-=1;
            }
            else if(currentMap[*y][*x-1]==BOX || currentMap[*y][*x-1]==FULLBOX)
            {
                if (currentMap[*y][*x-2]!=WALL && currentMap[*y][*x-2]!=BOX && currentMap[*y][*x-2]!=FULLBOX)
                {
                    if(currentMap[*y][*x-2]==NOTHING)
                    {
                        if(currentMap[*y][*x-1]==FULLBOX)
                        {
                            currentMap[*y][*x-1]=OVERTARGET;
                            currentMap[*y][*x-2]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *x-=1;
                        }
                        else if(currentMap[*y][*x-1]==BOX)
                        {   currentMap[*y][*x-1]=PLAYER;
                            currentMap[*y][*x-2]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *x-=1;

                        }
                        
                    }
                    else if(currentMap[*y][*x-2]==TARGET)
                    {
                        if(currentMap[*y][*x-1]==FULLBOX)
                        {
                            currentMap[*y][*x-1]=OVERTARGET;
                            currentMap[*y][*x-2]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *x-=1;
                        }
                        else if(currentMap[*y][*x-1]==BOX)
                        {
                            currentMap[*y][*x-1]=PLAYER;
                            currentMap[*y][*x-2]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *x-=1;  
                        }
                    }
                 }
            }
        

    }
}


static void goDown(unsigned int *y, unsigned int *x , char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET)
    {
       
        
        
            if(currentMap[*y+1][*x]==NOTHING)
            {
                currentMap[*y+1][*x]=PLAYER;
                currentMap[*y][*x]=TARGET;
                *y+=1;
                
            }
            else  if(currentMap[*y+1][*x]==TARGET)
            {
                currentMap[*y+1][*x]=OVERTARGET;
                currentMap[*y][*x]=TARGET;
                *y+=1;
            }
            else if(currentMap[*y+1][*x]==BOX || currentMap[*y+1][*x]==FULLBOX)
            {
                if (currentMap[*y+2][*x]!=WALL && currentMap[*y+2][*x]!=BOX && currentMap[*y+2][*x]!=FULLBOX)
                {
                    if(currentMap[*y+2][*x]==NOTHING)
                    {
                        if(currentMap[*y+1][*x]==FULLBOX)
                        {
                            currentMap[*y+1][*x]=OVERTARGET;
                            currentMap[*y+2][*x]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *y+=1;
                        }
                        else if(currentMap[*y+1][*x]==BOX)
                        {   currentMap[*y+1][*x]=PLAYER;
                            currentMap[*y+2][*x]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *y+=1;

                        }
                        
                    }
                    else if(currentMap[*y+2][*x]==TARGET)
                    {
                        if(currentMap[*y+1][*x]==FULLBOX)
                        {
                            currentMap[*y+1][*x]=OVERTARGET;
                            currentMap[*y+2][*x]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *y+=1;
                        }
                        else if(currentMap[*y+1][*x]==BOX)
                        {
                            currentMap[*y+1][*x]=PLAYER;
                            currentMap[*y+2][*x]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *y+=1;  
                        }
                    }
                 }
            }
        
    }
    else
    {
        
            if(currentMap[*y+1][*x]==NOTHING)
            {
                currentMap[*y+1][*x]=PLAYER;
                currentMap[*y][*x]=NOTHING;
                *y+=1;
                
            }
            else  if(currentMap[*y+1][*x]==TARGET)
            {
                currentMap[*y+1][*x]=OVERTARGET;
                currentMap[*y][*x]=NOTHING;
                *y+=1;
            }
            else if(currentMap[*y+1][*x]==BOX || currentMap[*y+1][*x]==FULLBOX)
            {
                if (currentMap[*y+2][*x]!=WALL && currentMap[*y+2][*x]!=BOX && currentMap[*y+2][*x]!=FULLBOX)
                {
                    if(currentMap[*y+2][*x]==NOTHING)
                    {
                        if(currentMap[*y+1][*x]==FULLBOX)
                        {
                            currentMap[*y+1][*x]=OVERTARGET;
                            currentMap[*y+2][*x]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *y+=1;
                        }
                        else if(currentMap[*y+1][*x]==BOX)
                        {   currentMap[*y+1][*x]=PLAYER;
                            currentMap[*y+2][*x]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *y+=1;

                        }
                        
                    }
                    else if(currentMap[*y+2][*x]==TARGET)
                    {
                        if(currentMap[*y+1][*x]==FULLBOX)
                        {
                            currentMap[*y+1][*x]=OVERTARGET;
                            currentMap[*y+2][*x]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *y+=1;
                        }
                        else if(currentMap[*y+1][*x]==BOX)
                        {
                            currentMap[*y][*x-1]=PLAYER;
                            currentMap[*y+2][*x]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *y+=1;  
                        }
                    }
                 }
            }
        

    }
}








static void goUp(unsigned int *y, unsigned int *x , char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET)
    {
       
        
        
            if(currentMap[*y-1][*x]==NOTHING)
            {
                currentMap[*y-1][*x]=PLAYER;
                currentMap[*y][*x]=TARGET;
                *y-=1;
                
            }
            else  if(currentMap[*y-1][*x]==TARGET)
            {
                currentMap[*y-1][*x]=OVERTARGET;
                currentMap[*y][*x]=TARGET;
                *y-=1;
            }
            else if(currentMap[*y-1][*x]==BOX || currentMap[*y-1][*x]==FULLBOX)
            {
                if (currentMap[*y-2][*x]!=WALL && currentMap[*y-2][*x]!=BOX && currentMap[*y-2][*x]!=FULLBOX)
                {
                    if(currentMap[*y-2][*x]==NOTHING)
                    {
                        if(currentMap[*y-1][*x]==FULLBOX)
                        {
                            currentMap[*y-1][*x]=OVERTARGET;
                            currentMap[*y-2][*x]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *y-=1;
                        }
                        else if(currentMap[*y-1][*x]==BOX)
                        {   currentMap[*y-1][*x]=PLAYER;
                            currentMap[*y-2][*x]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *y-=1;

                        }
                        
                    }
                    else if(currentMap[*y-2][*x]==TARGET)
                    {
                        if(currentMap[*y-1][*x]==FULLBOX)
                        {
                            currentMap[*y-1][*x]=OVERTARGET;
                            currentMap[*y-2][*x]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *y-=1;
                        }
                        else if(currentMap[*y-1][*x]==BOX)
                        {
                            currentMap[*y-1][*x]=PLAYER;
                            currentMap[*y-2][*x]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *y-=1;  
                        }
                    }
                 }
            }
        
    }
    else
    {
       
            if(currentMap[*y-1][*x]==NOTHING)
            {
                currentMap[*y-1][*x]=PLAYER;
                currentMap[*y][*x]=NOTHING;
                *y-=1;
                
            }
            else  if(currentMap[*y-1][*x]==TARGET)
            {
                currentMap[*y-1][*x]=OVERTARGET;
                currentMap[*y][*x]=NOTHING;
                *y-=1;
            }
            else if(currentMap[*y-1][*x]==BOX || currentMap[*y-1][*x]==FULLBOX)
            {
                if (currentMap[*y-2][*x]!=WALL && currentMap[*y-2][*x]!=BOX && currentMap[*y-2][*x]!=FULLBOX)
                {
                    if(currentMap[*y-2][*x]==NOTHING)
                    {
                        if(currentMap[*y-1][*x]==FULLBOX)
                        {
                            currentMap[*y-1][*x]=OVERTARGET;
                            currentMap[*y-2][*x]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *y-=1;
                        }
                        else if(currentMap[*y-1][*x]==BOX)
                        {   currentMap[*y-1][*x]=PLAYER;
                            currentMap[*y-2][*x]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *y-=1;

                        }
                        
                    }
                    else if(currentMap[*y-2][*x]==TARGET)
                    {
                        if(currentMap[*y-1][*x]==FULLBOX)
                        {
                            currentMap[*y-1][*x]=OVERTARGET;
                            currentMap[*y-2][*x]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *y-=1;
                        }
                        else if(currentMap[*y-1][*x]==BOX)
                        {
                            currentMap[*y][*x-1]=PLAYER;
                            currentMap[*y-2][*x]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *y-=1;  
                        }
                    }
                 }
            }
        

    }
}