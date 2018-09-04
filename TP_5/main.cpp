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

	/*Se le da a cada Worm una posicion inicial aleatoria dentro de los limites y las teclas con las que reaccionara cada uno*/
	wormPArray[0]->set_pos(rand() % (SCENARIO_RIGHT_EDGE - SCENARIO_LEFT_EDGE) + SCENARIO_LEFT_EDGE, SCENARIO_FLOOR);
	wormPArray[0]->set_keys(UP_KEYCODE, LEFT_KEYCODE, RIGHT_KEYCODE);
	wormPArray[1]->set_pos(rand() % (SCENARIO_RIGHT_EDGE - SCENARIO_LEFT_EDGE) + SCENARIO_LEFT_EDGE, SCENARIO_FLOOR);
	wormPArray[1]->set_keys(W_KEYCODE, A_KEYCODE, D_KEYCODE);

	wormCount = 2;	//Cuantos worms hay

	if (init(&eventGen, &grapher))
	{
		while (!eventGen->is_quit())	//Si el evento no es de salida, continua SE SALE CON q.
		{
			if (eventGen->is_event())	//Chequea si hay eventos
			{
				dispatch(eventGen->get_event(), wormCount, wormPArray, grapher);	//Cede el control a una funcion u otra dependiendo del evento.
			}
		}
	}
	delete grapher;
	delete eventGen;
}

bool init(EventGenerator ** eventGen, Grapher ** grapher)
{
	*grapher = new Grapher(XDISPLAY, YDISPLAY);	//Grapher inicializa a su vez Allegro y el display de Allegro.
	if ((*grapher)->init_has_failed())			//Chequea fallo
	{
		return false;
	}
	*eventGen = new EventGenerator();			//eventGen inicializa a su vez la cola de eventos y el timer de Allegro.
	if ((*eventGen)->init_has_failed())			//Chequea fallo
	{
		return false;
	}
	return true;
}