#include <iostream>
#include "EventGenerator.h"
#include "Event.h"
#include "Grapher.h"
#include "Worm.h"
#include "dispatch.h"
#include <ctime>
#include <cstdlib>

#define XDISPLAY			1920
#define YDISPLAY			696
#define UP_KEYCODE			84
#define	DOWN_KEYCODE		85
#define	LEFT_KEYCODE		82
#define	RIGHT_KEYCODE		83
#define W_KEYCODE			23
#define A_KEYCODE			1
#define D_KEYCODE			4
#define SCENARIO_LEFT_EDGE	680
#define SCENARIO_RIGHT_EDGE	1175
#define SCENARIO_FLOOR		616

using namespace std;
bool init(EventGenerator ** eventGen, Grapher ** grapher);

int main(int argc, char *argv[])
{
	EventGenerator * eventGen= NULL;
	Grapher * grapher = NULL;

	srand(time(NULL));

	Worm * wormPArray[] = {NULL, NULL};
	Worm w1, w2;
	int wormCount;
	wormPArray[0] = &w1;
	wormPArray[1] = &w2;
	wormPArray[0]->set_pos(rand() % (SCENARIO_RIGHT_EDGE - SCENARIO_LEFT_EDGE) + SCENARIO_LEFT_EDGE, SCENARIO_FLOOR);
	wormPArray[0]->set_keys(UP_KEYCODE, LEFT_KEYCODE, RIGHT_KEYCODE);
	wormPArray[1]->set_pos(rand() % (SCENARIO_RIGHT_EDGE - SCENARIO_LEFT_EDGE) + SCENARIO_LEFT_EDGE, SCENARIO_FLOOR);
	wormPArray[1]->set_keys(W_KEYCODE, A_KEYCODE, D_KEYCODE);

	wormCount = 2;

	if (init(&eventGen, &grapher))
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

bool init(EventGenerator ** eventGen, Grapher ** grapher)
{
	*grapher = new Grapher(XDISPLAY, YDISPLAY);
	if ((*grapher)->init_has_failed())
	{
		return false;
	}
	*eventGen = new EventGenerator();
	if ((*eventGen)->init_has_failed())
	{
		return false;
	}
	return true;
}