#include <stdio.h>
#include <stdlib.h>

#include "levelLoader.h"
#include "levelSaver.h"

int main(int argc, char *argv[]) 
{
	//testLevelLoader();
	readLevelsFile("data/level/levels.lvl");
	saveLevels("data/level/levels3.lvl");

	return(0); 
}