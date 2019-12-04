#include "../headers/biquadris.h"
#include "../headers/block.h"
#include "../headers/square.h"

namespace Biquadris
{
	std::map<std::string, Block*> defaults;
	int seed = 0;

	const int MAX_LEVEL = 5;

	void init(int seed)
	{
		Biquadris::seed = seed;

		defaults["I"] = new Block({
		  new Square(0, 3, "I", 0, SquareStatus::ACTIVE),
		  new Square(1, 3, "I", 0, SquareStatus::ACTIVE),
		  new Square(2, 3, "I", 0, SquareStatus::ACTIVE),
		  new Square(3, 3, "I", 0, SquareStatus::ACTIVE)
			});

		defaults["J"] = new Block({
		  new Square(0, 2, "J", 2, SquareStatus::ACTIVE),
		  new Square(0, 3, "J", 2, SquareStatus::ACTIVE),
		  new Square(1, 3, "J", 2, SquareStatus::ACTIVE),
		  new Square(2, 3, "J", 2, SquareStatus::ACTIVE)
			});

		defaults["L"] = new Block({
		  new Square(0, 3, "L", 3, SquareStatus::ACTIVE),
		  new Square(1, 3, "L", 3, SquareStatus::ACTIVE),
		  new Square(2, 3, "L", 3, SquareStatus::ACTIVE),
		  new Square(2, 2, "L", 3, SquareStatus::ACTIVE)
			});

		defaults["O"] = new Block({
		  new Square(0, 3, "O", 4, SquareStatus::ACTIVE),
		  new Square(0, 2, "O", 4, SquareStatus::ACTIVE),
		  new Square(1, 3, "O", 4, SquareStatus::ACTIVE),
		  new Square(1, 2, "O", 4, SquareStatus::ACTIVE)
			});

		defaults["S"] = new Block({
		  new Square(0, 3, "S", 5, SquareStatus::ACTIVE),
		  new Square(1, 3, "S", 5, SquareStatus::ACTIVE),
		  new Square(1, 2, "S", 5, SquareStatus::ACTIVE),
		  new Square(2, 2, "S", 5, SquareStatus::ACTIVE)
			});

		defaults["Z"] = new Block({
		  new Square(0, 2, "Z", 6, SquareStatus::ACTIVE),
		  new Square(1, 2, "Z", 6, SquareStatus::ACTIVE),
		  new Square(1, 3, "Z", 6, SquareStatus::ACTIVE),
		  new Square(2, 3, "Z", 6, SquareStatus::ACTIVE)
			});

		defaults["T"] = new Block({
		  new Square(0, 2, "T", 7, SquareStatus::ACTIVE),
		  new Square(1, 3, "T", 7, SquareStatus::ACTIVE),
		  new Square(1, 2, "T", 7, SquareStatus::ACTIVE),
		  new Square(2, 2, "T", 7, SquareStatus::ACTIVE)
			});
	}
}
