#pragma once
class EventGenerator
{
public:
	EventGenerator();
	~EventGenerator();

	bool is_event();
	eventType get_event();
	bool is_quit();

private:
	eventType ev;
};

