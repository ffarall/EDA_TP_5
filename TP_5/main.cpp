#include <iostream>
#include "EventGenerator.h"
#include "Event.h"
#include "Grapher.h"
#include "Worm.h"
#include "dispatch.h"



using namespace std;

int main(int argc, char *argv[])
{
	// INITS
	Worm * wormPArray[2];
	Worm w1(), w2();
	wormPArray[1] = &w1;
	wormPArray[2] = &w2;
	EventGenerator eventGen;
	while (!eventGen.is_quit())
	{
		if (eventGen.is_event())
		{
			dispatch(eventGen.get_event(), wormPArray);
		}

	}

	// DESTROYS
}