#include "Worm.h"
#include "dispatch.h"

#include "Event.h"

void dispatch(Event ev, int wormCount, Worm * wArray[], Grapher * grapher)
{
	switch (ev.get_event_type())
	{
		case POSSIBLE_WORM_MOVE:
		case POSSIBLE_WORM_STOP:
			for (int i = 0; i < wormCount; i++)		//Itera todos los worms
			{
				wArray[i]->update(ev);				//Actualiza propiedades de cada Worm
			}
			break;

		case REFRESH:
			for (int i = 0; i < wormCount; i++)		//Itera todos los worms
			{
				wArray[i]->update(ev);				//increment frameCount of worm.
				grapher->update(wArray, wormCount);	//Actualiza el display con la informacion de cada Worm
			} 
			break;

		default:
			break;
	}
}