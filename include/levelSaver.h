/**
 * @file levelSaver.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief En tête du programme sauvegardant les niveaux en mémoire.
 * 
 */
#ifndef __LEVEL_SAVER_H__
#define __LEVEL_SAVER_H__

#include "levelLoader.h"

/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à sauvegarder dans un fichier les niveaux précédemment chargés.
 *    
 * @param destination Chemin d'accès du fichier de sauvegarde
 */
extern void saveLevels(char *destination);

/**
 * @brief Fonction supprimant de la mémoire la file des niveaux.
 */
extern void freeNode(void);

/**
 * @brief Fonction supprimant de la mémoire les paramètres temporaires d'un niveau.
 * Attention : cette fonction n'enlève pas le niveau de la file !
 * 
 * @param level Strcuture du niveau dont les membres temporaires sont à supprimer
 */
extern void freeLevel(Level *level);

/**
 * @brief Fonction de test du levelSaver et levelLoader.
 */
extern void testLevelLoadAndSave(void);


#endif