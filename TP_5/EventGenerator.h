#pragma once
#include "Event.h"
#include <allegro5/allegro.h>

#define FPS	50

class EventGenerator
{
public:
	EventGenerator();
	~EventGenerator();
	
	/*is_event*/
	//Devuelve si hay algun evento que espere ser atendido
	bool is_event();

	/*get_event*/
	//Devuelve el proximo evento que espera ser atendido
	Event get_event();

	/*is_quit*/
	//Devuelve si el evento indica finalizacion el programa
	bool is_quit();

	/*init_has_failed*/
	//Devuelve si fallo la inicializacion del EventGenerator
	//Relacionado con inicializadores del timer y eventqueue de Allegro.
	bool init_has_failed();


private:
	Event event;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	bool initError;
};

