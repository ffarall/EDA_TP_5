#include "Event.h"



Event::Event()
{
	type = -1;
}

Event::Event(int type)
{
	this->type = type;
}

int Event::get_event_type()
{
	return type;
}

char Event::get_key_event_unichar()
{
	return keyUniChar;
}

void Event::set_type(int type)
{
	this->type = type;
}

void Event::set_key_event_unichar(int keyUniChar)
{
	this->keyUniChar = keyUniChar;
}


