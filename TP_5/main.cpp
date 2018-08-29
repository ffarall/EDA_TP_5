#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	// INITS
	Worm * wormPArray[2];
	Worm w1(), w2();
	wormPArray[1] = &w1;
	wormPArray[2] = &w2;

	while (!eventGen.is_quit())
	{
		if (eventGen.is_event())
		{
			dispatch(eventGen.get_event(), wormPArray);
		}
	}

	// DESTROYS
}