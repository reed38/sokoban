

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXSIZE 10

int configureTerminal()
{
	struct termios new;
	if (tcgetattr(0,&new)==-1) {
      		perror("tcgetattr");
		return -1;
    	}
	new.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	new.c_lflag &= ~(ECHO);   // les touches tapées ne s'inscriront plus dans le terminal
	new.c_cc[VMIN]=1;
	new.c_cc[VTIME]=0;
	if (tcsetattr(0,TCSANOW,&new)==-1) {
      		perror("tcsetattr");
		return 0;
	}
	return 1;
}

void terminalReset()
{
	system("clear");

}


void terminalRefresh(char *map, int maxHeight)
{
	terminalReset();
	for (int i=0;i<maxHeight;i++)
	{
		printf("%s\n",map[i]);
	}

}
