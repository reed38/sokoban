/**
 * @file levelSaver.c
 * @author Esteban CADIC, Noé MOREAU, Edgar REGNAULT
 * @brief Programme sauvegardant les niveaux en mémoire.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "levelSaver.h"
#include "levelLoader.h"

void saveLevels(char *destination)
{
    FILE *saveFile = NULL;

	saveFile = fopen(destination, "w");
	if (saveFile == NULL)
	{
		fprintf(stderr, "Erreur lors de l'ouverture du fichier de sauvegarde...\n");
		perror("");
		exit(0);
	}

    Level *ptr = levelsNode;
    
    while (ptr != NULL)
    {
        fprintf(saveFile, ";LEVEL %d\n", ptr->levelNumber);

        if (ptr->comment != NULL)
            fprintf(saveFile, ";COMMENT %s\n", ptr->comment); 
    
        if (ptr->author != NULL)
            fprintf(saveFile, ";AUTHOR %s\n", ptr->author); 

        fprintf(saveFile, ";SUCCESS %d\n", ptr->success);

        for (int i=0; i<(ptr->numberLines); i++)
        {
           fprintf(saveFile, "%s\n", ptr->map[i]); 
        }
        


		ptr = ptr->nextLevel;
	}

    fclose(saveFile);
}
