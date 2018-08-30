#pragma once
#include <string>

using namespace std;

enum Events { POSSIBLE_WORM_MOVE , REFRESH};
class Event
{
public:
	Event();
	Event(int type);
	int get_event_type();
	char get_key_event_unichar();
	void set_type(int type);
	void set_key_event_unichar(int keyUniChar);

private:
	int type;
	int keyUniChar;
};

