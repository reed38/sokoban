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
	struct Level *nextLevel; /**< Lien au niveau suivant */
} Level;


/*------------------------------------------------------------------------------
	GLOBAL VARIABLES
------------------------------------------------------------------------------*/
/**
 * @brief File contenant tous les niveaux.
 */
extern Level *levelsNode;


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à charger en mémoire un fichier contenant des tableaux.
 * Elle initialise la file contenant tous les niveaux avec tous les paramètres du fichier.
 *   
 * @param location Chemin d'accès du fichier 
 */
extern void readLevelsFile(char *);

/**
 * @brief Fonction servant à initaliser les paramètres temporaires d'un niveau.
 * Elle détermine les coordonées du joueur dans le tableau 2D en mettant à jour les membres playerX et playerY de la structure du niveau.
 * Elle copie defaultMap dans map afin de garder une copie de l'originale pour la sauvegarde. 
 * Ne pas oublier d'appeler freeLevel(Level *) une fois le niveau terminé. 
 * 
 * @param level Structure du niveau que l'on souhaite initialiser
 */
extern void initLevel(Level **);

/**
 * @brief Fonction de test du levelLoader et du  levelSaver.
 */
extern void testLevelLoadAndSave(void);


#endif