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
	char *author; /**< Auteur du tableau */
	char *comment; /**< Commentaire */
	char success; /**< Indicateur de résolution du niveau */
	char **map; /**< Tableau 2D réprésentant le tableau du fichier (map) */
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
 * @brief Fonction servant à déterminer les coordonées du joueur dans le tableau 2D.
 * Si le joueur existe, elle met à jour les membres playerX et playerY de la structure du niveau.
 * 
 * @param level Structure du niveau duquel on souhaite déterminer la position du joueur
 */
extern void determinePlayerCoord(Level *);

/**
 * @brief Fonction de test du levelLoader.
 */
extern void testLevelLoader(void);

#endif