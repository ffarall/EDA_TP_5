#pragma once
#include <string>

using namespace std;

enum Events {POSSIBLE_WORM_MOVE , REFRESH, POSSIBLE_WORM_STOP, QUIT, VOID};

class Event
{
public:
	Event();
	Event(int type);

	/*get_event_type*/
	//Devuelve el tipo del evento
	int get_event_type();

	/*get_key_event_keycode*/
	//Devuelve el codigo keycode de la tecla presionada o soltada
	char get_key_event_keycode();

	/*set_type*/
	//Setea un evento con un tipo determinado
	void set_type(int type);

	/*set_key_event_keycode*/
	//Setea la variable con el codigo keycode de la tecla presionada o soltada
	void set_key_event_keycode(int keycode);

private:
	int type;			//Tipo de evento
	int keycode;		//Codigo keycode de la tecla presionada o soltada
};

