/**
 * @file keys.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme de détection des appuis de touches sur le terminal.
 *
 */
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "movements.h"

/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static int readKeyboard(void);

/**
 * @brief Fonction servant à lire la touche pressée.
 * Cette fonction est bloquante.
 *
 * @return int Code de la touche lue.
 */
static int readKeyboard(void)
{
	char buff[MAXSIZE];
	int c;

	if ((c = read(0, buff, 3)) == -1) // Si read échoue
		return 0;

	switch (buff[0])
	{
	case 27:
		if ((c == 3) && (buff[1] == 91))
			return (buff[2] - 64);
		else
			return 0;
		break;
	default:
		return buff[0];
		break;
	}
}

void interactionLoop(/*char *saveFile*/)
{
	for (;;)
	{
		switch (readKeyboard())
		{
		case UP:
			move(UP);
			break;
		case DOWN:
			 move(DOWN);
			break;
		case RIGHT:
			 move(RIGHT);
			break;
		case LEFT:
			 move(LEFT);
			break;
		case 'z':
			// steps.c
			break;
		case 'r':
			// freeLevel(currentLevel);
			// initLevel(currentLevel);
			break;
		case 't':
			// steps.c
			break;
			/*case 's':
				saveLevels(saveFile);
				printf("\nPartie sauvegardée !\n");
				break;
			case 'q': 
			printf("\nMerci d'avoir joué !\n");
			saveLevels("data/level/levels3.lvl");*/
			// TODO : freeLevel(currentLevel)
			//freeNode();
			return;
		}
		printLevel(globalCurrent);
	}
}
