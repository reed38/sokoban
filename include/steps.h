/**
 * @file steps.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief 
 * 
 */
#ifndef __STEPS_H__
#define __STEPS_H__

#include "levelLoader.h"

/*------------------------------------------------------------------------------
	MACROS
------------------------------------------------------------------------------*/

// TODO : virer ça, déjà présent dans le movement.h
#define BOX			'$'
#define WALL		'#'
#define PLAYER		'@'
#define TARGET  	'.'
#define NOTHING		' '
#define FULLBOX		'Q'
#define OVERTARGET	'O'

// TODO : virer ça, déjà présent dans le keys.h
#define UP          1
#define DOWN        2
#define RIGHT       3
#define LEFT        4

/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/

/**
 * @brief Structure représentant un déplacement.
 * 
 */
typedef struct Step { 
	unsigned char direction; /**< Direction du déplacement */
	unsigned char cellReplaced; /**< Cellule que le joueur à remplacée */
	unsigned char cellReplacedPlus; /**< Cellule se trouvant après la cellule que le joueur à remplacée (dans la même direction) */
	struct Step *previousStep; /**< Lien vers le déplacement précédent */
} Step;

/*------------------------------------------------------------------------------
	GLOBAL VARIABLES
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/

extern void addStep(Step **, unsigned char, unsigned char, unsigned char);

extern void backStep(Level *level);

/**
 * @brief Fonction récupérant une chaine représentant un trajet, effectuant les mouvements et ajoute sur la pile d'étapes
 * @param steps pile des mouvements
 * @param str chaine représentant un trajet
 */
extern void stepsParser(Step **steps, char *str);

extern void testSteps(void);


#endif