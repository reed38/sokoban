/**
 * @file steps.h
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief En-tête du programme de gestion de l'historique des déplacements.
 * 
 */
#ifndef __STEPS_H__
#define __STEPS_H__

#include "levelLoader.h"


/*------------------------------------------------------------------------------
	TYPE DEFINITIONS
------------------------------------------------------------------------------*/

/**
 * @brief Structure représentant un déplacement.
 * 
 */
typedef struct Step { 
	unsigned char direction; /**< Direction du déplacement */
	unsigned char cellReplaced; /**< Cellule que le joueur a remplacée */
	unsigned char cellReplacedPlus; /**< Cellule se trouvant après la cellule que le joueur a remplacée (dans la même direction) */
	struct Step *previousStep; /**< Lien vers le déplacement précédent */
} Step;


/*------------------------------------------------------------------------------
	DECLARATIONS
------------------------------------------------------------------------------*/


/**
 * @brief Fonction servant à ajouter une étape sur la pile des déplacements.
 *
 * @param steps Pile des déplacements
 * @param direction Direction du déplacement
 * @param cellReplaced Objet remplacé par le joueur
 * @param cellReplacedPlus Objet présent 2 cases devant le joueur dans sa direction de déplacement (ou 1 case devant après le déplacement)
 */
extern void addStep(Step **steps, unsigned char direction, unsigned char cellReplaced, unsigned char cellReplacedPlus);

/**
 * @brief Fonction annulant un déplacement en cours de jeu.
 *
 * @param level Niveau en cours de jeu
 */
extern void backStep(Level *level);

/**
 * @brief Fonction servant à interpréter une chaîne de caractères de déplacements et les ajoutant sur la pile des déplacements.
 *
 * @param steps Pile des déplacements
 * @param str Chaîne de caractères représentant une suite de déplacements à convertir
 */
extern void stepsParser(Step **steps, char *str);

/**
 * @brief Fonction servant à convertir la pile des déplacements en chaîne de caractères.
 * Penser à free la chaîne une fois récupérée !
 *
 * @param steps Pile des déplacements
 * @return str Chaîne de caractères représentant une suite de déplacements
 */
extern char *stepsSerialiser(Step *steps);

/**
 * @brief Fonction testant la gestion des déplacements (pile, parser/serializer).
 */
extern void testSteps(void);


#endif