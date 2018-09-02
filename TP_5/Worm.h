#pragma once
#include "Vector.h"
#include "Event.h"

#define WORM_SPEED 4.5
#define WORM_GRAVITY 0.24
#define PI 3.14159

typedef enum { START_MOVING, MOVING, STOP_MOVING, IDLE, START_JUMPING, JUMPING, LANDING } wormState_n;
typedef enum { KEY_MOVE_RIGHT_DOWN, KEY_MOVE_LEFT_DOWN, KEY_MOVE_UP, NEW_FRAME, KEY_JUMP_DOWN, NOT_VALID } wormEvent_n;
typedef unsigned int uint;
typedef struct
{
	wormState_n nextState;
	void(*action_routine) (void * p);
} wormFsmCell_n;

void no_act_routine(void * worm_);
void turn_worm(void * worm_);
void refresh_start_moving(void * worm_);
void refresh_moving(void * worm_);
void refresh_stop_moving(void * worm_);
void start_jumping(void * worm_);
void refresh_start_jumping(void * worm_);
void refresh_landing(void * worm_);
void refresh_jumping(void * worm_);


class Worm
{
public:
	Worm();
	Worm(Vector pos_);
	Worm(Vector pos_, char ku, char kl, char kr);
	Worm(int x_, int y_, char ku, char kl, char kr);
	Worm(int x_, int y_);
	~Worm();

	Vector get_pos();
	bool get_orientation();
	uint get_frameCounter();
	char get_event();
	wormState_n get_currentState();
	double get_jumpSpeed();
	double get_gravity();
	double get_angle();
	char get_keyUp();
	char get_keyLeft();
	char get_keyRight();

	void set_pos(Vector pos_);
	void set_pos(int x_, int y_);
	void set_x(int x_);
	void set_y(int y_);
	void inc_x(int x_);
	void inc_y(int y_);
	void set_keys(char ku, char kl, char kr);
	void set_orientation(bool orient);
	void inc_frameCounter();
	void set_frameCounter(uint fc);
	void set_currentState(wormState_n st);

	void update(Event& ev);
	void move();

private:
	wormState_n currentState;
	Vector pos;
	char keyUp;
	char keyRight;
	char keyLeft;
	const double jumpSpeed = WORM_SPEED;
	const double g = WORM_GRAVITY;
	const double angle = PI / 3.0;
	bool lookingRight;
	uint frameCounter;

	uint jumpDuration;
	char ev;

	wormEvent_n event_decoder(Event& ev_);
};

