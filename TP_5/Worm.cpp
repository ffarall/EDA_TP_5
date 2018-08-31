#include "Worm.h"
#include <cstdlib>


Worm::Worm()
{
}

Worm::Worm(Vector pos_): pos(pos_)
{
	currentState = RESTING;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
}

Worm::Worm(double x_, double y_): pos(x_, y_)
{
	currentState = RESTING;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
}


Worm::~Worm()
{
}


