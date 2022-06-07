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
#include "steps.h"

/*------------------------------------------------------------------------------
	VARIABLES
------------------------------------------------------------------------------*/

Level *levelsNode = NULL;


/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static inline int startWith(char *, char *);
static inline char* removeKeyword(char *);
static void parseLine(char *);
static Level* insertLevel(unsigned int); 
static void insertInfo(char **, char *);
static void generateMap(char ***, unsigned int *,  char *);


/*------------------------------------------------------------------------------
	FONCTIONS
------------------------------------------------------------------------------*/

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

	// On supprime les fins de ligne (CR et/ou LF) (évite de nombreux problèmes)
	if(strchr(line, '\r') != NULL)
		line[strcspn(line, "\r")] = '\0'; 
	if(strchr(line, '\n') != NULL)
		line[strcspn(line, "\n")] = '\0'; 

	if(startWith(";LEVEL", line)) // Mot clef LEVEL
	{
		currentLevel = insertLevel(atoi(removeKeyword(line)));
		//listeAffiche();
	} 
	else if(startWith(";COMMENT", line)) // Mot clef COMMENT
	{
		insertInfo(&(currentLevel->comment), removeKeyword(line));
	}
	else if(startWith(";AUTHOR", line)) // Mot clef AUTHOR
	{
		insertInfo(&(currentLevel->author), removeKeyword(line));
	}
	else if(startWith(";SUCCESS", line)) // Mot clef SUCCESS
	{
		currentLevel->success = atoi(removeKeyword(line));
	}
	else if(startWith(";STEPS", line)) // Mot clef STEPS
	{
		stepsParser(&currentLevel->stepsNode, removeKeyword(line));
	}
	else // Pas de mot clef : c'est une ligne d'un tableau
	{
		if(levelsNode == NULL)
			return;
		
		generateMap(&(currentLevel->defaultMap), &(currentLevel->numberLines), line);
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
	lv->comment = NULL;
	lv->author = NULL;
	lv->success = 0;
	lv->numberMov = 0;
	lv->numberPush = 0;
	lv->defaultMap = NULL;
	lv->map = NULL;
	lv->numberLines = 0;
	lv->stepsNode = NULL;
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
 * @brief Fonction servant à copier une chaîne de caractères vers un emplacement mémoire.
 * Utilisée ici afin d'insérer une information dans un membre de la stucture d'un niveau (auteur, commentaire...).
 * 
 * @param member Pointeur vers un emplacement de la mémoire (peut être NULL)
 * @param args Information à placer dans la mémoire
 */
static void insertInfo(char **member, char *args) 
{
	*member = (char *) malloc((strlen(args) + 1) * sizeof(char));
	if(*member == NULL) 
	{
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}
	strcpy(*member, args);
}

/**
 * @brief Fonction permetant de générer un tableau 2D (map) à partir de lignes d'un tableau. 
 * La fonction va rajouter la ligne du tableau passée en paramètre à la fin de le map.
 * Chaque ligne du tableau se termine par \0 (chaîne de caractères). 
 * 
 * @param defaultMap Pointeur vers la map a qui on veut rajouter une ligne, **defaultMap peut être NULL
 * @param numberLines Pointeur vers le nombre de lignes de la map
 * @param line Chaîne de caracères à ajouter à la map
 */
static void generateMap(char ***defaultMap, unsigned int *numberLines, char *line)
{
	/*
	 * Cette fonction va créer une map temporaire de la taille de la map originale +1 afin
	 * de stocker une nouvelle ligne du tableau. Il faut bien penser à alouer dynamiquement
	 * de la mémoire pour notre ligne afin de la mettre dans la map... Puis on fait pointer
	 * notre ancienne map sur notre nouvelle 
	 */

	char **newMap = (char **) realloc(*defaultMap, (*numberLines + 1) * sizeof(char*));
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

	*defaultMap = newMap;
	*numberLines += 1;
}

// TODO : Remplacer '@' par le membre de l'enum
void initLevel(Level *level)
{
	char playerFound = 0;

	// Mise des scores à 0
	level->numberMov = 0;
	level->numberPush = 0;

	// Détermination de la position du joueur
	// TODO : ne pas oublier d'inverser dans movement
	for(int y = 0; y <= level->numberLines && !playerFound; y++) 
	{
		char element = ' '; 
		for(int x = 0; element != '\0' && !playerFound; x++)
		{
			element = level->defaultMap[y][x];
			if(element == '@')
			{
				level->playerX = x;
				level->playerY = y;
				playerFound = 1;
			}
		}
	}

	// Copie de defaultMap dans map pour la modification
	level->map = malloc((level->numberLines) * sizeof(char*));
	if(level->map == NULL) 
	{
		fprintf(stderr, "Mémoire insuffisante !\n");
		exit(1);
	}
	
	for(int i = 0; i < level->numberLines; i++)
	{
  		level->map[i] = malloc(strlen(level->defaultMap[i]) + 1);
  		strcpy(level->map[i], level->defaultMap[i]);
	}
}