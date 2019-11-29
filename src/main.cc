#include <iostream>

#include "biquadris.h"

using namespace std;

int main() {

	Biquadris::init();

	cout << *Biquadris::defaults['I'];

	int level;
	cin >> level;

	// ^ Are we getting input for level?

	return 0;
}
