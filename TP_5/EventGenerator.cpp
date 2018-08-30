#include "EventGenerator.h"

using namespace std;

EventGenerator::EventGenerator()
{
	event_queue = NULL;
	timer = NULL;
	initError = false;
	event_queue = al_create_event_queue();
	if (!event_queue) 
	{
		initError = true;
	}
	timer = al_create_timer(1.0 / FPS);
	if (!timer) 
	{
		initError = true;
	}

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
}

Event EventGenerator::get_event()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);
	if (ev.type == ALLEGRO_EVENT_TIMER)
	{
		event.set_type(REFRESH);
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		event.set_type(POSSIBLE_WORM_MOVE);
		event.set_key_event_unichar(ev.keyboard.unichar);
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		event.set_type(POSSIBLE_WORM_STOP);
		event.set_key_event_unichar(ev.keyboard.unichar);
	}

	return event;

}

bool EventGenerator::is_event()
{
	if (al_event_queue_is_empty(event_queue))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool EventGenerator::is_quit()
{
	return false;

}

bool EventGenerator::init_has_failed()
{
	return initError;
}

void EventGenerator::destroy()
{
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}