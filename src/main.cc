#include <iostream>
#include <string>

#include "biquadris.h"
#include "level.h"

using namespace std;

int main(int argc, string argv[]) {
	Biquadris::init();

	cout << *Biquadris::defaults['I'];

	string command;
	while(cin >> command) {
		int level;
		cin >> level;
	}
	// ^ Are we getting input for level?

	return 0;
}
