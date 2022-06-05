#include "levelLoader.h"
#include <stdio.h>
#include <stdlib.h>

// Parceque voir aucune fuite de mémoires avec valgrind ça fait plaisir
void freeNode(void) {
    Level *ptrFollow = levelsNode;
    Level *precPtdr = NULL;

	while (ptrFollow != NULL) {
        
        for(int i = 0; i != ptrFollow->numberLines; i++) {
            //printf("Supression map lv %d, ligne %d\n", ptrFollow->levelNumber, i);
            free(ptrFollow->map[i]);
        }
        free(ptrFollow->map);
        precPtdr = ptrFollow;
		ptrFollow = ptrFollow->nextLevel;
        free(precPtdr);
        //printf("Supression du lv terminee !\n");
	}
}

int main(int argc, char *argv[]) 
{
    readLevelsFile("data/level/levels2.lvl");

    freeNode();
	return(0); 
}