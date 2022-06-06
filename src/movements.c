#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "keys.h"
#include "movements.h"

static void goRight(unsigned int *y, unsigned int *x,unsigned int max, char **currentMap);
static void goLeft(unsigned int *y, unsigned int *x, unsigned int max, char **currentMap);
static void goUp(unsigned int *y, unsigned int *x, unsigned int max,char **currentMap);
static void goDown(unsigned int *y, unsigned int *x,unsigned int max, char **currentMap);


/**
 * @brief détecte l'input du joueur, puis modifie les coordonnées du joueur et
 * l'état de la map en conséquence
 * 
 * @param x coordonnée x du joueur
 * @param y coordonnée y du joueur
 * @param currentMap map modifiée par les actions du joueur
 */
/*void move(unsigned int *y, unsigned int *x, unsigned int linesNumber, char **currentMap)
{
    enum Keys  order=getInput();
    switch (order)
    {
        case RIGHT:
            goRight(x,y,strlen(currentMap[*y]), currentMap);
            break;
        case LEFT:
            goLeft(x,y,strlen(currentMap[*y]),currentMap);
            break;
        case DOWN:
            goDown(x,y,linesNumber,currentMap);
            break;
        case UP:
            goUp(x,y,linesNumber,currentMap);
            break;
        default:
            move(x,y,linesNumber,currentMap);
    }

}*/
//bug strlen ne permet pas ici d'obtenir la largeur de la ligne 
//pas forcément nécessaire de vérrifier
void move(unsigned int *y, unsigned int *x, unsigned int linesNumber, char **currentMap)
{
    enum Keys  order=getInput();
    switch (order)
    {
        case RIGHT:
            goRight(x,y,20, currentMap);
            break;
        case LEFT:
            goLeft(x,y,20, currentMap);
            break;
        case DOWN:
            goDown(x,y,20, currentMap);
            break;
        case UP:
            goUp(x,y,20, currentMap);
            break;
        default:
            move(x,y,20, currentMap);
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

    

static void goRight(unsigned int *y, unsigned int *x,unsigned int max, char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET) //premier cas le personnage est déja sur une target
    {
       
        
        
        if (*x+1<max) //on vérrifie qu'il n'y a pas d'overflow
        {
            if(currentMap[*y][*x+1]==NOTHING)
            {
                currentMap[*y][*x+1]=PLAYER;
                currentMap[*y][*x]=TARGET;
                *x+=1;
                
            }
            else  if(currentMap[*y][*x+1]==TARGET)
            {
                currentMap[*y][*x+1]=OVERTARGET;
                currentMap[*y][*x]=TARGET;
                *x+=1;
            }
            else if(currentMap[*y][*x+1]==BOX || currentMap[*y][*x+1]==FULLBOX)
            {
                if (*x+2<max && currentMap[*y][*x+2]!=WALL && currentMap[*y][*x+2]!=BOX && currentMap[*y][*x+2]!=FULLBOX)
                {
                    if(currentMap[*y][*x+2]==NOTHING)
                    {
                        if(currentMap[*y][*x+1]==FULLBOX)
                        {
                            currentMap[*y][*x+1]=OVERTARGET;
                            currentMap[*y][*x+2]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *x+=1;
                        }
                        else if(currentMap[*y][*x+1]==BOX)
                        {   currentMap[*y][*x+1]=PLAYER;
                            currentMap[*y][*x+2]=BOX;
                            currentMap[*y][*x]=TARGET;
                            *x+=1;

                        }
                        
                    }
                    else if(currentMap[*y][*x+2]==TARGET)
                    {
                        if(currentMap[*y][*x+1]==FULLBOX)
                        {
                            currentMap[*y][*x+1]=OVERTARGET;
                            currentMap[*y][*x+2]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *x+=1;
                        }
                        else if(currentMap[*y][*x+1]==BOX)
                        {
                            currentMap[*y][*x+1]=PLAYER;
                            currentMap[*y][*x+2]=FULLBOX;
                            currentMap[*y][*x]=TARGET;
                            *x+=1;  
                        }
                    }
                 }
            }
        }
    }
    
    else  //deuxième cas le personnage n'est pas sur une target
    {
        if (*x+1<max) //on vérrifie qu'il n'y a pas d'overflow
        {
            if(currentMap[*y][*x+1]==NOTHING)
            {
                currentMap[*y][*x+1]=PLAYER;
                currentMap[*y][*x]=NOTHING;
                *x+=1;
                
            }
            else  if(currentMap[*y][*x+1]==TARGET)
            {
                currentMap[*y][*x+1]=OVERTARGET;
                currentMap[*y][*x]=NOTHING;
                *x+=1;
            }
            else if(currentMap[*y][*x+1]==BOX || currentMap[*y][*x+1]==FULLBOX)
            {
                if (*x+2<max && currentMap[*y][*x+2]!=WALL && currentMap[*y][*x+2]!=BOX && currentMap[*y][*x+2]!=FULLBOX)
                {
                    if(currentMap[*y][*x+2]==NOTHING)
                    {
                        if(currentMap[*y][*x+1]==FULLBOX)
                        {
                            currentMap[*y][*x+1]=OVERTARGET;
                            currentMap[*y][*x+2]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *x+=1;
                        }
                        else if(currentMap[*y][*x+1]==BOX)
                        {   currentMap[*y][*x+1]=PLAYER;
                            currentMap[*y][*x+2]=BOX;
                            currentMap[*y][*x]=NOTHING;
                            *x+=1;

                        }
                        
                    }
                    else if(currentMap[*y][*x+2]==TARGET)
                    {
                        if(currentMap[*y][*x+1]==FULLBOX)
                        {
                            currentMap[*y][*x+1]=OVERTARGET;
                            currentMap[*y][*x+2]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *x+=1;
                        }
                        else if(currentMap[*y][*x+1]==BOX)
                        {
                            currentMap[*y][*x+1]=PLAYER;
                            currentMap[*y][*x+2]=FULLBOX;
                            currentMap[*y][*x]=NOTHING;
                            *x+=1;  
                        }
                    }
                 }
            }
        }
    }
}

static void goLeft(unsigned int *y, unsigned int *x,unsigned int max, char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET)
    {
       
        
        if (*x-1>=0)
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
                if (*x-2>=0 && currentMap[*y][*x-2]!=WALL && currentMap[*y][*x-2]!=BOX && currentMap[*y][*x-2]!=FULLBOX)
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
    }
    else
    {
        if (*x-1>=0)
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
                if (*x-2>=0 && currentMap[*y][*x-2]!=WALL && currentMap[*y][*x-2]!=BOX && currentMap[*y][*x-2]!=FULLBOX)
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
}


static void goDown(unsigned int *y, unsigned int *x,unsigned int max, char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET)
    {
       
        
        if (*y+1<max)
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
                if (*y+2<max && currentMap[*y+2][*x]!=WALL && currentMap[*y+2][*x]!=BOX && currentMap[*y+2][*x]!=FULLBOX)
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
    }
    else
    {
        if (*y+1<max)
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
                if (*y+2<max && currentMap[*y+2][*x]!=WALL && currentMap[*y+2][*x]!=BOX && currentMap[*y+2][*x]!=FULLBOX)
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
}








static void goUp(unsigned int *y, unsigned int *x,unsigned int max, char **currentMap)
{
    if(currentMap[*y][*x]==OVERTARGET)
    {
       
        
        if (*y-1>=0)
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
                if (*y-2>=0 && currentMap[*y-2][*x]!=WALL && currentMap[*y-2][*x]!=BOX && currentMap[*y-2][*x]!=FULLBOX)
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
    }
    else
    {
        if (*y-1>=0)
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
                if (*y-2>=0 && currentMap[*y-2][*x]!=WALL && currentMap[*y-2][*x]!=BOX && currentMap[*y-2][*x]!=FULLBOX)
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
}












