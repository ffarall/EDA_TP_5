#include <iostream>
#include "EventGenerator.h"
#include "Event.h"
#include "Grapher.h"
#include "Worm.h"
#include "dispatch.h"

#define XDISPLAY	1920
#define YDISPLAY	696

using namespace std;
bool init(EventGenerator * eventGen, Grapher * grapher);

int main(int argc, char *argv[])
{
	EventGenerator * eventGen= NULL;
	Grapher * grapher = NULL;
	Worm * wormPArray[] = {NULL, NULL};
	Worm w1, w2;
	int wormCount;
	wormPArray[0] = &w1;
	wormPArray[1] = &w2;
	wormCount = 2;

	if (init(eventGen, grapher))
	{
		while (!eventGen->is_quit())
		{
			if (eventGen->is_event())
			{
				dispatch(eventGen->get_event(), wormCount, wormPArray, grapher);
			}
		}
	}
	grapher->destroy();
	eventGen->destroy();
}

bool init(EventGenerator * eventGen, Grapher * grapher)
{
	grapher = new Grapher(XDISPLAY, YDISPLAY);
	if (grapher->init_has_failed())
	{
		return false;
	}
	eventGen = new EventGenerator();
	if (eventGen->init_has_failed())
	{
		return false;
	}
	return true;
}