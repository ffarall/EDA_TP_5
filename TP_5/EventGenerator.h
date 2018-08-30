#pragma once
#include "Event.h"
#include <allegro5/allegro.h>

#define FPS	50

class EventGenerator
{
public:
	EventGenerator();
	

	bool is_event();
	Event get_event();
	bool is_quit();
	bool init_has_failed();
	void destroy();

private:
	Event event;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	bool initError;
};

