    #ifndef __MOVEMENTS_H__
    #define __MOVEMENTS_H__
    #define BOX '$'
    #define WALL '#'
    #define PLAYER '@'
    #define TARGET '.'
    #define NOTHING ' '
    #define FULLBOX 'Q'
    #define OVERTARGET 'O'

    void move(unsigned int *y, unsigned int *x, unsigned int linesNumber, char **currentMap);


    #endif
