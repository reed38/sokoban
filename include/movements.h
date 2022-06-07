/**
 * @file movements.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief En-tête du programme de gestion des mouvements du joueur.
 * 
 */
#ifndef __MOVEMENTS_H__
#define __MOVEMENTS_H__

#include "levelLoader.h"

/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

#define BOX '$'
#define WALL '#'
#define PLAYER '@'
#define TARGET '.'
#define NOTHING ' '
#define FULLBOX 'Q'
#define OVERTARGET 'O'


/*------------------------------------------------------------------------------
	GLOBAL VARIABLES
------------------------------------------------------------------------------*/

/**
 * @brief Niveau en cours de jeu.
 * 
 */
extern Level *globalCurrentLevel;


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

/**
 * @brief Fonction servant à modifier les coordonnées du joueur dans le tableau selon une direction.
 *
 * @param direction Direction dans laquelle on souhaite déplacer le joueur
 */
extern void move(int direction);

/**
 * @brief Fonction de test des mouvements. 
 * 
 */
extern void testMovements(void);

#endif