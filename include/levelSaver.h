/**
 * @file levelSaver.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief En tête du programme sauvegardant les niveaux en mémoire.
 * 
 */
#ifndef __LEVEL_SAVER_H__
#define __LEVEL_SAVER_H__

/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à sauvegarder en mémoire un fichier contenant des tableaux de jeu.
 *    
 * @param destination Chemin d'accès du fichier de sauvegarde
 */
extern void saveLevels(char *);

/**
 * @brief Fonction de test du levelSaver et levelLoader.
 */
extern void testLevelLoadAndSave(void);


#endif