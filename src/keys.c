#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "keys.h"
#include "movements.h"
#define MAXSIZE 10

/**
 * @brief permet de lire la touche pressée et retourne un int correspondant 
 * @return int corresondant
 */
int litClavier()
{
	char r[MAXSIZE];
	int c;

	if ((c=read(0,r,3)) == - 1 ) return 0;

	switch (r[0]) {
		case 27 :  if ((c==3) && (r[1]==91)) return (r[2]-64); else return 0; break;
		default: return r[0]; break;
	}
}
/**
 * @brief scan la touche presse 
 * @return enum Keys 
 */
enum Keys getInput(void)
{
	int a=litClavier();

	switch(a)
	{
		case 1:
			return UP;
			break;
		case 2:
			return DOWN;
			break;
		case 3:
			return RIGHT;
			break;
		case 4:
			return LEFT;
			break;
		case 98:
			return BACK;
		case 114:
			return RESET;
			break;
		default:
			getInput();
		break;
	}
}

