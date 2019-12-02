#include <iostream>
#include <string>
#include <sstream>

#include "biquadris.h"
#include "level.h"

using namespace std;

int main(int argc, char* argv[]) {
	//Initialization
	Biquadris::init();

	bool showWindow = true;

	for(int i = 1; i < argc; i++) {
		string arg(argv[i]);
		if(arg == "text") {
			showWindow = false;
		}
		else if(arg == "seed") {
			//Ensure there are still enough paramaters to satsisfy seed option
			if((i+1) < argc) {
				int tempSeed;
				stringstream ss(argv[i]);

				if(ss >> tempSeed) {
					Biquadris::seed = tempSeed;
				}
				else {
					cout << "Warning: invalid seed provided, must be an integer" << endl;
				}
			}
			else {
				cout << "Warning: no seed provided" << endl;
			}
		}
	}

	string command;
	while(cin >> command) {
		int level;
		cin >> level;
	}
	// ^ Are we getting input for level?

	return 0;
}
