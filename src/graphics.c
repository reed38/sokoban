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
	printHeader(level->levelNumber, level->author, level->comment);
	printMap(level->map, level->numberLines);
	printFooter(level->success);
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
 * @brief Fonction servant à afficher la map avec des couleurs
 *
 * @param map Tableau 2D
 * @param maxHeight Nombre de lignes du tableau
 */
static void printMap(char **map, int maxHeight)
{
	for (int i = 0; i < maxHeight; i++)
	{
		for (int j = 0; j < strlen(map[i]); j++)
		{
			//TODO : remplacer les char par les macro (PLAYER etc)
			switch (map[i][j])
			{
			case '@': //PLAYER
				printf(ANSI_CODE_RED "%c" ANSI_CODE_RESET, map[i][j]);
				break;

			case '$': //BOX
				printf(ANSI_CODE_YELLOW "%c" ANSI_CODE_RESET, map[i][j]);
				break;

			case '.': //TARGET
				printf(ANSI_CODE_GREEN "%c" ANSI_CODE_RESET, map[i][j]);
				break;

			case 'Q': //FULLBOX
				printf(ANSI_CODE_BLUE "%c" ANSI_CODE_RESET, map[i][j]);
				break;	

			case 'O': //OVERTARGET
				printf(ANSI_CODE_CYAN "%c" ANSI_CODE_RESET, map[i][j]);
				break;		
			
			default: //WALLS et NOTHING
				printf("%c", map[i][j]);
				break;
			}
		}
		printf("\n");
	}

	printf("\n");
}

/**
 * @brief affiche l'en-tête du jeu (titre, noms, niveau, auteur, commentaire)
 * 
 * @param levelNumber numéro du niveau
 * @param author auteur du niveau
 * @param comment commentaire sur le niveau
 */
static void printHeader(unsigned int levelNumber, char *author, char *comment)
{
	printf(ANSI_CODE_BG_BLUE ANSI_CODE_BOLD ANSI_CODE_UNDERLINE "Super Sokoban par Esteban CADIC, Noé MOREAU, Edgar REGNAULT" ANSI_CODE_RESET);
	printf("\n\n");
	printf(ANSI_CODE_BOLD ANSI_CODE_GREEN "Niveau numéro %d\n" ANSI_CODE_RESET, levelNumber);
	if(author != NULL)
		printf(ANSI_CODE_CYAN "Auteur : %s" ANSI_CODE_RESET, author);
	else
		printf(ANSI_CODE_CYAN "Auteur : inconnu" ANSI_CODE_RESET);

	if(comment != NULL)
	{
		printf(ANSI_CODE_CYAN " | Commentaire : %s" ANSI_CODE_RESET, comment);
	}
		
	printf("\n\n");
}

/**
 * @brief affiche les commandes disponibles en bas de terminal selon si le niveau est réussi ou non
 * 
 * @param success réussite du niveau
 */
static void printFooter(char success)
{
	if (success)
	{
		printf(ANSI_CODE_YELLOW "Bravo, vous avez réussi ce niveau !\n");
		printf(ANSI_CODE_MAGENTA "Appuyez sur t pour revoir votre trajet\n" ANSI_CODE_RESET);
	}

	else
	{
		printf(ANSI_CODE_MAGENTA "Deplacer le joueur avec les fleches du clavier\n");
		printf("z : annuler\tr : recommencer\n" ANSI_CODE_RESET);
	}

}
