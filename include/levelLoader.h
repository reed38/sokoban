#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/
/**
 * @brief Structure représentant un niveau.
 * 
 * 
 */
typedef struct Level { 
    unsigned int levelNumber; /**< Numéro du niveau */
    char **map; /**< Tableau 2D réprésentant le tableau du fichier (map) */
    unsigned int numberLines; /**< Nombre de ligne du tableau */
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
extern void readLevelsFile(char *location);

#endif