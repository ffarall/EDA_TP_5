#include "EventGenerator.h"

#define Q_KEYCODE	17

using namespace std;

EventGenerator::EventGenerator(): event()
{
	event_queue = NULL;
	timer = NULL;
	initError = false;
	event_queue = al_create_event_queue();	//Crea cola de eventos
	if (!event_queue)	//Chequea error
	{
		initError = true;
	}
	else 
	{
		timer = al_create_timer(1.0 / FPS);	//Crea timer
		if ((!timer) || (!al_install_keyboard()))	//Chequea error
		{
			initError = true;
		}
		else
		{
			/*Se asocia eventos con la cola de eventos*/
			al_register_event_source(event_queue, al_get_timer_event_source(timer));
			al_register_event_source(event_queue, al_get_keyboard_event_source());

			al_start_timer(timer);
		}	
	}
	
}

EventGenerator::~EventGenerator()
{
	if(event_queue)
		al_destroy_event_queue(event_queue);	//Destruye cola de eventos
	if(timer)
		al_destroy_timer(timer);				//Destruye timer
}

Event EventGenerator::get_event()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(event_queue, &ev);
	switch (ev.type)								//Se genera el evento dependiendo del tipo de evento de Allegro
	{
		case ALLEGRO_EVENT_TIMER:
			event.set_type(REFRESH);
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (ev.keyboard.keycode == Q_KEYCODE)	//Q es la tecla para salir del programa. 
			{
				event.set_type(QUIT);				//Si se presiona la Q el evento sera de tipo QUIT
			}
			else
			{
				event.set_type(POSSIBLE_WORM_MOVE);
			}
			event.set_key_event_keycode(ev.keyboard.keycode);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			event.set_type(POSSIBLE_WORM_STOP);
			event.set_key_event_keycode(ev.keyboard.keycode);
			break;
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
	if (event.get_event_type() == QUIT)
	{
		return true;
	}
	else 
	{
		return false;
	}

}

bool EventGenerator::init_has_failed()
{
	return initError;
}
