#include "Event.h"

Event::Event()
{
	type = VOID;			//Para evitar errores el evento comienza "sin tipo"
}

Event::Event(int type)
{
	this->type = type;	//Setea tipo
}

int Event::get_event_type()
{
	return type;
}

char Event::get_key_event_keycode()
{
	return keycode;
}

void Event::set_type(int type)
{
	this->type = type;		//Setea tipo
}

void Event::set_key_event_keycode(int keycode)
{
	this->keycode = keycode;	//Setea codigo keycode
}


