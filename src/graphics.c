#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"

/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static inline void refreshTerminal(void);
static void printMap(char **, int);
static void printHeader(unsigned int, char *, char *);
static void printFooter(char);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à effacer le terminal.
 * 
 */
static inline void refreshTerminal(void)
{
	printf("\e[1;1H\e[2J"); // Séquence d'échappement permettant d'effacer le terminal
}

void printLevel(Level *level)
{
	// A modifier avec les bonnes valeurs après les tests
	refreshTerminal();
	printHeader(5, "Coucou c'est moi !!!!", "Un petit commentaire");
	printMap(level->map, level->numberLines);
	printFooter(0);
}

void configureTerminal(void)
{
	struct termios terminalSetup;
	if (tcgetattr(0, &terminalSetup) == -1)
	{
		perror("tcgetattr");
		exit(1);
	}
	terminalSetup.c_lflag &= ~(ICANON); // Met le terminal en mode canonique.
	terminalSetup.c_lflag &= ~(ECHO);	// Les touches tapées ne s'inscriront plus dans le terminal
	terminalSetup.c_cc[VMIN] = 1;		// Nombre minimum de caractères lors d'une lecture en mode non canonique.
	terminalSetup.c_cc[VTIME] = 0;		// Délai en dixièmes de seconde pour une lecture en mode non canonique.
	if (tcsetattr(0, TCSANOW, &terminalSetup) == -1) // tcsetattr() indique une réussite si une des modifications peut être réalisée
	{ 
		perror("tcsetattr");
		exit(1);
	}
}

/**
 * @brief Fonction servant à afficher la map
 *
 * @param map Tableau 2D
 * @param maxHeight Nombre de lignes du tableau
 */
static void printMap(char **map, int maxHeight)
{
	for (int i = 0; i < maxHeight; i++)
	{
		printf("%s\n", map[i]);
	}
}

/**
 * @brief 
 * 
 * @param levelNumber 
 * @param author 
 * @param comment 
 */
static void printHeader(unsigned int levelNumber, char *author, char *comment)
{
	printf(ANSI_CODE_BG_BLUE ANSI_CODE_BOLD ANSI_CODE_UNDERLINE "Super Sokoban par Esteban CADIC, Noé MOREAU, Edgar REGNAULT" ANSI_CODE_RESET);
	printf("\n\n");
	printf(ANSI_CODE_BOLD ANSI_CODE_GREEN "Niveau numéro %d" ANSI_CODE_RESET, levelNumber);
	if(author != NULL)
		printf("\t\tAuteur : %s", author);

	if(comment != NULL)
	{
		printf("\n");
		printf("%s", comment);
	}
		
	printf("\n\n");
}

/**
 * @brief 
 * 
 * @param success 
 */
static void printFooter(char success)
{
	// controles et messages qui dit si success : "vous avez compléter ce niveau, appuyer sur p pour voir votre trajet !"
	// controles différents si succes ou pas !
}
