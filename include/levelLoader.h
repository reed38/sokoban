/**
 * @file levelLoader.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief En tête du programme chargeant les niveaux en mémoire.
 * 
 */
#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/
/**
 * @brief Structure représentant un niveau.
 * 
 */
typedef struct Level { 
	unsigned int levelNumber; /**< Numéro du niveau */
	char *comment; /**< Commentaire */
	char *author; /**< Auteur du tableau */
	char success; /**< Indicateur de résolution du niveau */
	unsigned int numberMov; /**< Nombre de mouvements effectués */
	unsigned int numberPush; /**< Nombre de déplacements de caisses effectués */
	char **defaultMap; /**< Tableau 2D (map) réprésentant le tableau dans le fichier de niveaux. Ne doit pas être modifié. */
	char **map; /**< Tableau 2D (map) réprésentant le tableau en cours du jeu */
	unsigned int numberLines; /**< Nombre de ligne du tableau */
	/*@{*/
	unsigned int playerX; /**< Abscisse du joueur dans la map */
	unsigned int playerY; /**< Ordonnée du joueur dans la map */
	/*@}*/
	struct Step *stepsNode; /**< Pile des déplacements effectués */
	struct Level *nextLevel; /**< Lien au niveau suivant */
} Level;


/*------------------------------------------------------------------------------
	GLOBAL VARIABLES
------------------------------------------------------------------------------*/
/**
 * @brief File contenant tous les niveaux.
 */
extern Level *levelsNode;

/**
 * @brief Niveau en cours de jeu.
 * 
 */
extern Level *globalCurrentLevel;


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à charger en mémoire un fichier contenant des tableaux.
 * Elle initialise la file contenant tous les niveaux avec tous les paramètres du fichier.
 *   
 * @param location Chemin d'accès du fichier 
 */
extern void readLevelsFile(char *location);

/**
 * @brief Fonction servant à initaliser / réinitialiser les paramètres temporaires d'un niveau.
 * Elle détermine les coordonées du joueur dans le tableau 2D en mettant à jour les membres playerX et playerY de la structure du niveau.
 * Elle copie defaultMap dans map afin de garder une copie de l'originale pour la sauvegarde. 
 * Ne pas oublier d'appeler freeLevel(Level *) une fois le niveau terminé ou avant la réinitialisation. 
 * 
 * @param level Structure du niveau que l'on souhaite initialiser
 * @param reset Indique si on doit recommencer le niveau (supprimer les déplacements)
 */
extern void initLevel(Level *level, char reset);

/**
 * @brief Fonction déterminant si l'on peut passer au niveau précédent
 * Renvoie 1 si le niveau précédent est atteingnable (ie si on n'est pas au niveau 1) ; 0 sinon
 * 
 * @param level Niveau actuel
 */
extern char isPreviousReachable(Level *level);

/**
 * @brief Fonction déterminant si l'on peut passer au niveau suivant
 * Renvoie si le niveau suivant est atteignable (s'il y a un niveau après ET si le niveau actuel est résolu) ; 0 sinon
 * 
 * @param level Niveau actuel
 */
extern char isNextReachable(Level *level);

/**
 * @brief Charge le niveau suivant
 * @param level Niveau actuel
 */
extern void loadNextLevel(void);

/**
 * @brief Charge le niveau précédent
 * @param level Niveau actuel
 */
extern void loadPreviousLevel(void);


/**
 * @brief Fonction de test du levelLoader et du levelSaver.
 */
extern void testLevelLoadAndSave(void);


#endif