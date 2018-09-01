#pragma once
#include "Vector.h"
#include "Event.h"

#define WORM_SPEED (27*50) // Worms move at 27 pixels per second, and frameCounter is 1/50 of a second (50 FPS)
#define WORM_GRAVITY 0.24
#define PI 3.14159

typedef enum { START_MOVING, MOVING, STOP_MOVING, RESTING, JUMP } wormState_n;
typedef enum { KEY_MOVE_RIGHT_DOWN, KEY_MOVE_LEFT_DOWN, KEY_MOVE_UP, NEW_FRAME, KEY_JUMP_DOWN } wormEvent_n;
typedef unsigned int uint;

class Worm
{
public:
	Worm();
	Worm(Vector pos_);
	Worm(Vector pos_, char ku, char kl, char kr);
	Worm(double x_, double y_, char ku, char kl, char kr);
	Worm(double x_, double y_);
	~Worm();

	Vector get_pos();
	bool get_orientation();
	uint get_frameCounter();

	void set_pos(Vector pos_);
	void set_pos(double x_, double y_);
	void set_orientation(bool orient);
	void set_frameCounter(uint fc);

	void update(Worm * wArray[], int wormCount);

private:
	wormState_n currentState;
	Vector pos;
	char keyUp;
	char keyRight;
	char keyLeft;
	const double speed = WORM_SPEED;
	const double g = WORM_GRAVITY;
	const double angle = PI / 3.0;
	bool lookingRight;
	uint frameCounter;

	uint jumpDuration;

	wormEvent_n event_decoder(Event& ev);
};

