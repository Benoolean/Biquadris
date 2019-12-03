#include <iostream>
#include <string>
#include <sstream>

#include "../headers/biquadris.h"
#include "../headers/level.h"

using namespace std;

int main(int argc, char* argv[])
{
	//Initialization
	Biquadris::init();

	bool showWindow = true;
	int startlevel = 0;
	vector<string> sourcefiles{ "media/sequence1.txt", "media/sequence2.txt" };

	for (int i = 1; i < argc; i++)
	{
		string arg(argv[i]);
		if (arg == "-text")
		{
			showWindow = false;
		}
		else if (arg == "-seed")
		{
			//Ensure there are still enough paramaters to satsisfy seed option
			if ((i + 1) < argc)
			{
				int tempSeed;
				stringstream ss(argv[i+1]);

				if (ss >> tempSeed)
				{
					Biquadris::seed = tempSeed;
				}
				else
				{
					cout << "Warning: invalid seed provided, must be an integer" << endl;
				}
			}
			else
			{
				cout << "Warning: no seed provided" << endl;
			}
		}
		else if (arg == "-startlevel")
		{
			//Ensure there are still enough paramaters to satsisfy seed option
			if ((i + 1) < argc)
			{
				int tempLevel;
				stringstream ss(argv[i+1]);

				if (ss >> tempLevel)
				{
					startlevel = tempLevel;
				}
				else
				{
					cout << "Warning: invalid level provided, must be an integer" << endl;
				}
			}
			else
			{
				cout << "Warning: no level provided" << endl;
			}
		}
		else if (arg == "-scriptfile1")
		{
			string source;
			if ((i + 1) < argc)
			{
				sourcefiles[0] = argv[i + 1];
			}
			else
			{
				cout << "Warning: no source provided" << endl;
			}
		}
		else if (arg == "-scriptfile2")
		{
			string source;
			if ((i + 1) < argc)
			{
				sourcefiles[1] = argv[i + 1];
			}
			else
			{
				cout << "Warning: no source provided" << endl;
			}
		}
	}

	Level level(startlevel, 2, showWindow, sourcefiles);

	level.StartGame();

	string command;
	while (cin >> command)
	{
		int level;
		cin >> level;
	}
	// ^ Are we getting input for level?

	return 0;
}
