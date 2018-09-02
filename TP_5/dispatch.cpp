#include "Worm.h"
#include "dispatch.h"
#include "Grapher.h"
#include "Event.h"

void dispatch(Event ev, int wormCount, Worm * wArray[], Grapher * grapher) // worm pointer
{
	switch (ev.get_event_type())
	{
		case POSSIBLE_WORM_MOVE:
		
			for (int i = 0; i < wormCount; i++)
			{
				wArray[i]->start_moving(ev.get_key_event_unichar());
			}
			break;

		case REFRESH:
			for (int i = 0; i < wormCount; i++)
			{
				wArray[i]->update(); //increment frameCount of worm.
				grapher->update(wArray, wormCount);

			} 
			break;

		case POSSIBLE_WORM_STOP:
			for (int i = 0; i < wormCount; i++)
			{
				wArray[i]->stop_moving(ev.get_key_event_unichar());
			}
			break;

		default:
			break;
	}
}