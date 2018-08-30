#include "Worm.h"
#include "dispatch.h"
#include "Event.h"

void dispatch(Event ev, Worm worm, Worm * wArray[]) // worm pointer
{
	int count = worm.get_count();
	switch (ev.get_event_type())
	{
		case POSSIBLE_WORM_MOVE:
		
			for (int i = 0; i < count; i++)
			{
				wArray[i]->start_moving(ev.get_key_event_unichar());
			}
			break;

		case REFRESH:
			for (int i = 0; i < count; i++)
			{
				wArray[i]->update(); // increment frameCount of worm.
				grapher.update(wArray, count);
			} 
			break;

		case POSSIBLE_WORM_STOP:
			for (int i = 0; i < count; i++)
			{
				wArray[i]->stop_moving(ev.get_key_event_unichar());
			}
			break;

		default:
			break;
	}
}