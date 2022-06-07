/**
 * @file keys.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme de détection des appuis de touches sur le terminal.
 *
 */
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "keys.h"
#include "graphics.h"
#include "levelLoader.h"
#include "levelSaver.h"
#include "movements.h"
#include "steps.h"

/*------------------------------------------------------------------------------
	PROTOTYPES
------------------------------------------------------------------------------*/

static int readKeyboard(void);


/**
 * @brief Fonction servant à lire la touche pressée.
 * Cette fonction est bloquante.
 * 
 * @return int Code de la touche lue.
 */
static int readKeyboard(void)
{
    char buff[MAXSIZE];
    int c;

    if ((c = read(0, buff, 3)) == -1) // Si read échoue
        return 0;

    switch (buff[0])
    {
    case 27:
        if ((c == 3) && (buff[1] == 91))
            return (buff[2] - 64);
        else
            return 0;
        break;
    default:
        return buff[0];
        break;
    }
}


void interactionLoop(char *saveFile)
{
    printLevel(globalCurrentLevel);

    for(;;)
    {
        switch (readKeyboard())
        {
        case UP:
            move(UP);
            break;
        case DOWN:
            move(DOWN);
            break;
        case RIGHT:
            move(RIGHT);
            break;
        case LEFT:
            move(LEFT);
            break;
        case 'z': // Annuler un déplacement
            // steps.c 
            break;
        case 'r': // Réinitialise le niveau
            freeLevel(globalCurrentLevel);
            initLevel(globalCurrentLevel);          
            break;
        case 't': // Revoir les déplacements effectués
            // steps.c    
            break;
        case 'p': // Niveau précédent    
            break;
        case 'n': // Niveau suivant 
            break;
        case 's': // Sauvegarder
            saveLevels(saveFile);
            printf("\nPartie sauvegardée !\n");
            break;
        case 'q': // Sauvegarder et quitter
            printf("\nMerci d'avoir joué !\n"); 
            saveLevels(saveFile);
            return;
        }

		printLevel(globalCurrentLevel);
    }
}
