/**
 * @file movements.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme de gestion des mouvements du joueur.
 * 
 */
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "keys.h"
#include "movements.h"

Level *globalCurrentLevel;

static void goRight(unsigned int *x, unsigned int *y);
static void goLeft(unsigned int *x, unsigned int *y);
static void goUp(unsigned int *x, unsigned int *y);
static void goDown(unsigned int *x, unsigned int *y);
static void checkFinished(void);

void move(int direction)
{
	// todo: à inverser
	unsigned int *y = &globalCurrentLevel->playerX;
	unsigned int *x = &globalCurrentLevel->playerY;

	switch (direction)
	{
	case RIGHT:
		goRight(x, y);
		break;
	case LEFT:
		goLeft(x, y);
		break;
	case DOWN:
		goDown(x, y);
		break;
	case UP:
		goUp(x, y);
		break;
	default:
		break;
	}

	checkFinished();
}

/**
 * @brief Fonction qui permet de déplacer le personnage à droite et d'intéragir aves les objets se trouvant à droite.
 *
 * @param x,y Coordonnées du joueur
 */
static void goRight(unsigned int *x, unsigned int *y)
{
	char **currentMap = globalCurrentLevel->map;

	// on différencie le cas où le personnage est sur une target et celui où il est sur rien
	char nextCase = (currentMap[*y][*x] == OVERTARGET) ? TARGET : NOTHING;

	if (currentMap[*y][*x + 1] == NOTHING)
	{
		currentMap[*y][*x + 1] = PLAYER;
		currentMap[*y][*x] = nextCase;
		*x += 1;
		globalCurrentLevel->numberMov += 1;
	}
	else if (currentMap[*y][*x + 1] == TARGET)
	{
		currentMap[*y][*x + 1] = OVERTARGET;
		currentMap[*y][*x] = nextCase;
		*x += 1;
		globalCurrentLevel->numberMov += 1;
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
			globalCurrentLevel->numberPush += 1;
			globalCurrentLevel->numberMov += 1;
		}
	}
}

/**
 * @brief Fonction qui permet de déplacer le personnage à gauche et d'intéragir aves les objets se trouvant à gauche.
 *
 * @param x,y Coordonnées du joueur
 */
static void goLeft(unsigned int *x, unsigned int *y)
{
	char **currentMap = globalCurrentLevel->map;
	char nextCase = (currentMap[*y][*x] == OVERTARGET) ? TARGET : NOTHING;

	if (currentMap[*y][*x - 1] == NOTHING)
	{
		currentMap[*y][*x - 1] = PLAYER;
		currentMap[*y][*x] = nextCase;
		*x -= 1;
		globalCurrentLevel->numberMov += 1;
	}
	else if (currentMap[*y][*x - 1] == TARGET)
	{
		currentMap[*y][*x - 1] = OVERTARGET;
		currentMap[*y][*x] = nextCase;
		*x -= 1;
		globalCurrentLevel->numberMov += 1;
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
			globalCurrentLevel->numberPush += 1;
			globalCurrentLevel->numberMov += 1;
		}
	}
}

/**
 * @brief Fonction qui permet de déplacer le personnage en bas et d'intéragir aves les objets se trouvant en bas.
 *
 * @param x,y Coordonnées du joueur
 */
static void goDown(unsigned int *x, unsigned int *y)
{
	char **currentMap = globalCurrentLevel->map;
	char nextCase = (currentMap[*y][*x] == OVERTARGET) ? TARGET : NOTHING;

	if (currentMap[*y + 1][*x] == NOTHING)
	{
		currentMap[*y + 1][*x] = PLAYER;
		currentMap[*y][*x] = nextCase;
		*y += 1;
		globalCurrentLevel->numberMov += 1;
	}
	else if (currentMap[*y + 1][*x] == TARGET)
	{
		currentMap[*y + 1][*x] = OVERTARGET;
		currentMap[*y][*x] = nextCase;
		*y += 1;
		globalCurrentLevel->numberMov += 1;
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
			globalCurrentLevel->numberPush += 1;
			globalCurrentLevel->numberMov += 1;
		}
	}
}

/**
 * @brief Fonction qui permet de déplacer le personnage en haut et d'intéragir aves les objets se trouvant en haut.
 *
 * @param x,y Coordonnées du joueur
 */
static void goUp(unsigned int *x, unsigned int *y)
{
	char **currentMap = globalCurrentLevel->map;
	char nextCase = (currentMap[*y][*x] == OVERTARGET) ? TARGET : NOTHING;

	if (currentMap[*y - 1][*x] == NOTHING)
	{
		currentMap[*y - 1][*x] = PLAYER;
		currentMap[*y][*x] = nextCase;
		*y -= 1;
		globalCurrentLevel->numberMov += 1;
	}
	else if (currentMap[*y - 1][*x] == TARGET)
	{
		currentMap[*y - 1][*x] = OVERTARGET;
		currentMap[*y][*x] = nextCase;
		*y -= 1;
		globalCurrentLevel->numberMov += 1;
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
				}
			}
			globalCurrentLevel->numberPush += 1;
			globalCurrentLevel->numberMov += 1;
		}
	}
}

/**
 * @brief Fonction servant à marquer un niveau comme terminé, une fois toutes les caisses placées sur les cibles.
 *
 */
void checkFinished(void)
{
	char **currentMap = globalCurrentLevel->map;
	for (int i = 0; i < globalCurrentLevel->numberLines; i++)
	{
		for (int j = 0; j < strlen(currentMap[i]); j++)
		{
			if (currentMap[i][j] == '$')
			{
				globalCurrentLevel->success = 0;
				return;
			}
		}
	}
	globalCurrentLevel->success = 1;
}