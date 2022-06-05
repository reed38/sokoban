/**
 * @file levelLoader.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme chargeant les niveaux en mémoire.
 * 
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "levelLoader.h"

/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/

Level *levelsNode = NULL;


/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static void parseLine(char *);
static Level* insertLevel(unsigned int); 
static void generateMap(char ***, unsigned int *,  char *);
static inline int startWith(char *, char *);
static inline char* removeKeyword(char *);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

// A virer à la fin, sert de débug
void listeAffiche(void)
{
	Level *ptrFollow = levelsNode;

	if (NULL == ptrFollow)
		printf("Liste vide!");
	else
		printf("Contenu de la liste : ");
	while (NULL != ptrFollow) {
		printf("%d ", ptrFollow->levelNumber);

		ptrFollow = ptrFollow->nextLevel;
	}
	printf("\n");
}

void readLevelsFile(char *location) 
{
	FILE *levelsFile = NULL;

	int lineLen = 0;
	long unsigned int lineSize = 0;
	char *lineBuffer = NULL; 

	levelsFile = fopen(location, "r");
	if (levelsFile == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier...\n");
		perror("");
		exit(0);
	}
	
    while ((lineLen = getline(&lineBuffer, &lineSize, levelsFile)) != -1) 
	{	// getline alloue dynamiquement un buffer pour la ligne
		parseLine(lineBuffer);
    }

	if(lineBuffer != NULL)
	{
		free(lineBuffer);
  		lineBuffer=NULL;
	}

	fclose(levelsFile);
}

/**
 * @brief Fonction servant à interpéter une ligne.
 * Chaque ligne du fichier de configuration est interprétée par cette fonction.
 * Pour les commandes (débutant par ;), elle sépare le mot clef des arguments et execute le code qui va avec le mot clef.
 * Pour les lignes des tableaux, elle construit la map 2D. 
 *   
 * @param line Chaîne de caractères a interpéter (peut être une commande ou un bout de tableau)
 */
static void parseLine(char *line) 
{
	static Level *currentLevel = NULL;

	if(startWith(";LEVEL", line)) // Mot clef LEVEL
	{
		char *args = removeKeyword(line);
		currentLevel = insertLevel(atoi(args));
		//listeAffiche();
	} 
	else // Pas de mot clef : c'est une ligne d'un tableau
	{
		if(levelsNode == NULL)
			return;
		
		generateMap(&(currentLevel->map), &(currentLevel->numberLines), line);
		//printf("-lvl = %d \t -ln = %d \t l = %s\n", currentLevel->levelNumber, (currentLevel->numberLines) - 1, currentLevel->map[(currentLevel->numberLines) - 1]);
	}
}

/**
 * @brief Fonction servant à insérer un niveau dans la file.
 * 
 * @param levelNumber Numéro du niveau à insérer
 * @return Level* Pointeur vers le dernier élement de file
 */
static Level* insertLevel(unsigned int levelNumber)
{
	Level *lv = malloc(sizeof(Level));
	if(lv == NULL) {
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}

	lv->levelNumber = levelNumber;
	lv->map = NULL;
	lv->numberLines = 0;
	lv->nextLevel = NULL;

	if (levelsNode == NULL) {	// Dans le cas où la liste est vide
		levelsNode = lv;
		return lv;
	}

	Level *ptrFollow = levelsNode;

	while (ptrFollow->nextLevel != NULL) {	// On cherche la liste qui a le lien vide
		ptrFollow = ptrFollow->nextLevel;
	}

	ptrFollow->nextLevel = lv;	// On fait pointer le dernier élément de la liste, à notre nouveau élément

	return lv;
}

/**
 * @brief Fonction permetant de générer un tableau 2D (map) à partir de lignes d'un tableau. 
 * La fonction va rajouter la ligne du tableau passée en paramètre à la fin de le map.
 * Chaque ligne du tableau se termine par \0 (chaîne de caractères). 
 * 
 * @param map Pointeur vers la map a qui on veut rajouter une ligne, **map peut être NULL
 * @param numberLines Pointeur vers le nombre de lignes de la map
 * @param line Chaîne de caracères à ajouter à la map
 */
static void generateMap(char ***map, unsigned int *numberLines, char *line)
{
	/*
	 * Cette fonction va créer une map temporaire de la taille de la map originale +1 afin
	 * de stocker une nouvelle ligne du tableau. Il faut bien penser à alouer dynamiquement
	 * de la mémoire pour notre ligne afin de la mettre dans la map... Puis on fait pointer
	 * notre ancienne map sur notre nouvelle 
	 */

	char **newMap = (char **) realloc(*map, (*numberLines + 1) * sizeof(char*));
	if(newMap == NULL) 
	{
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}

	newMap[*numberLines] = (char *) malloc((strlen(line) + 1) * sizeof(char));
	if(newMap[*numberLines] == NULL) 
	{
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}

	strcpy(newMap[*numberLines], line);
	*map = newMap;
	*numberLines += 1;
}

/**
 * @brief Fonction déterminant si une chaîne débute par un mot clef donné.
 * 
 * @param keyword Mot clef
 * @param command Commande
 * @return int 0 si le mot clef est trouvé, 1 sinon
 */
static inline int startWith(char *keyword, char *command) 
{
	return strncmp(keyword, command, strlen(keyword)) == 0;
}

/**
 * @brief Fonction qui supprime un mot clef d'une chaîne.
 * Chaque commande commence par un mot clef, suivie d'un espace.
 * La fonction renvoie tout ce qui suit l'espace.
 * 
 * @param command Commande
 * @return char* Pointeur vers le caractère suivant l'espace
 */
static inline char* removeKeyword(char *command) 
{
	char *args = command;
	while(*args && *args != ' ') 
    	args++;
	
	return ++args;
} 