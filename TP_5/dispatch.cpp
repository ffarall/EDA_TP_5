#include "Worm.h"
#include "dispatch.h"

#include "Event.h"

void dispatch(Event ev, int wormCount, Worm * wArray[], Grapher * grapher) // worm pointer
{
	switch (ev.get_event_type())
	{
		case POSSIBLE_WORM_MOVE:
		case POSSIBLE_WORM_STOP:
			for (int i = 0; i < wormCount; i++)
			{
				wArray[i]->update(ev);
			}
			break;

		case REFRESH:
			for (int i = 0; i < wormCount; i++)
			{
				wArray[i]->update(ev); //increment frameCount of worm.
				grapher->update(wArray, wormCount);
			} 
			break;

		default:
			break;
	}
}