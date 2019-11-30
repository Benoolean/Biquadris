#include <string>
#include <iostream>
#include "Level.h"

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

	level.SpawnBlock();

	// read in the command inputs
	string cmd = "";

	while (cin >> cmd)
	{
		if (cmd == "left")
		{

		}
	}

	return 0;
}
