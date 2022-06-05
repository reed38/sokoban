#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"

void terminalReset()
{
    system("clear");
}

int main()
{   
    char **map = (char **) malloc(10 * sizeof(char *));
    for (int line = 0; line < 10; line++)
        map[line] = (char *) malloc(20 * sizeof(char));

    for (int x = 0; x<10; x++)
        for (int y = 0; x<20; x++)
            map[x][y] = '#';

    //configureTerminal();
    for (;;)
    {
        /*int x;
        scanf("%d", &x);
        if (x == 0)
        {
            for (int i = 0; i < 20; i++)
            {
                printf("tutututuutututttutututututututututututuutututttutututututututututututuutututttutututututututu\n");
            }
        }
        else if (x == 1)
        {
            terminalReset();
        }*/
        terminalRefresh(map, 10);
        
        printf("MAP : %c\n", (*map)[10]);
        map[5][10] = '!';
        printf("MAP : %c\n", (*map)[10]);
        sleep(1);

        terminalRefresh(map, 10);
        sleep(1);
        //strcpy(map[5], "aaaaaaa");
    }
}