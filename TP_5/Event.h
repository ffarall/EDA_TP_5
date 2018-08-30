#pragma once
#include <string>

using namespace std;

enum Events {POSSIBLE_WORM_MOVE , REFRESH, POSSIBLE_WORM_STOP};

class Event
{
public:
	Event();
	Event(int type);

	/*get_event_type*/
	//Devuelve el tipo del evento
	int get_event_type();

	/*get_key_event_unichar*/
	//Devuelve el codigo unichar de la tecla presionada o soltada
	char get_key_event_unichar();

	/*set_type*/
	//Setea un evento con un tipo determinado
	void set_type(int type);

	/*set_key_event_unichar*/
	//Setea la variable con el codigo unichar de la tecla presionada o soltada
	void set_key_event_unichar(int keyUniChar);

private:
	int type;			//Tipo de evento
	int keyUniChar;		//Codigo unichar de la tecla presionada o soltada
};

