    #ifndef __MOVEMENTS_H__
    #define __MOVEMENTS_H__
    #include "levelLoader.h"
    #define BOX '$'
    #define WALL '#'
    #define PLAYER '@'
    #define TARGET '.'
    #define NOTHING ' '
    #define FULLBOX 'Q'
    #define OVERTARGET 'O'

    void move(unsigned int *y, unsigned int *x,  Level *levelPtr);


    #endif
