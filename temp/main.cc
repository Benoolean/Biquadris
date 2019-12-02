#include <string>
#include <iostream>
#include "Level.h"
#include "Square.h"

using namespace std;

int main(int argc, char* argv[])
{
	// read in commandline args
	for (int i = 3; i < argc; ++i) 
	{

	}
	
	// start game;
	Level level;
	level.StartGame();

	return 0;
}
