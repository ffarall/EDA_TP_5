#include "Worm.h"
#include <cstdlib>


Worm::Worm()
{
}

Worm::Worm(Vector pos_): pos(pos_)
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
}

Worm::Worm(Vector pos_, char ku, char kl, char kr): pos(pos_)
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
	keyUp = ku;
	keyRight = kr;
	keyLeft = kl;
}

Worm::Worm(double x_, double y_, char ku, char kl, char kr): pos(x_, y_)
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
	keyUp = ku;
	keyRight = kr;
	keyLeft = kl;
}

Worm::Worm(double x_, double y_): pos(x_, y_)
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
}


Worm::~Worm()
{
}

wormEvent_n Worm::event_decoder(Event& ev)
{
	char evChar = ev.get_key_event_unichar();
	switch (ev.get_event_type())
	{
	case POSSIBLE_WORM_MOVE: 
	{
		if (evChar == keyLeft)
		{
			return KEY_MOVE_LEFT_DOWN;
		}
		else if (evChar == keyRight)
		{
			return KEY_MOVE_RIGHT_DOWN;
		}
		else if (evChar == keyUp)
		{
			return KEY_JUMP_DOWN;
		}
	} break;
	case POSSIBLE_WORM_STOP:
	{
		if (evChar == keyLeft || evChar == keyRight)
		{
			return KEY_MOVE_UP;
		}
	} break;
	case REFRESH:
	{
		return NEW_FRAME;
	} break;
	default:
		break;
	}
}

void Worm::update(Event& ev)
{
	const wormFsmCell_n wormFsm[WORM_FSM_EVENTS][WORM_FSM_STATES] =
	{ // START_MOVING,							MOVING,							STOP_MOVING,						IDLE,						JUMPING
		{{START_MOVING, no_act_routine},		{MOVING, no_act_routine},		{MOVING, turn_worm},				{START_MOVING, turn_worm},	{JUMPING, no_act_routine}},		// KEY_MOVE_RIGHT_DOWN
		{{START_MOVING, no_act_routine},		{MOVING, no_act_routine},		{MOVING, turn_worm},				{START_MOVING, turn_worm},	{JUMPING, no_act_routine}},		// KEY_MOVE_LEFT_DOWN
		{{IDLE, no_act_routine},				{STOP_MOVING, no_act_routine},	{STOP_MOVING, no_act_routine},		{IDLE, no_act_routine},		{JUMPING, no_act_routine}},		// KEY_MOVE_UP
		{{START_MOVING, refresh_start_moving},	{MOVING, refresh_moving},		{STOP_MOVING, refresh_stop_moving},	{IDLE, no_act_routine},		{JUMPING, refresh_jumping}},	// NEW_FRAME
		{{JUMPING, no_act_routine},				{JUMPING, no_act_routine},		{JUMPING, no_act_routine},			{JUMPING, no_act_routine},	{JUMPING, no_act_routine}}		// KEY_JUMP_DOWN
	};

	wormEvent_n wormEv = event_decoder(ev);
	wormState_n wormSt = currentState;
	currentState = wormFsm[wormEv][wormSt].nextState;
	(wormFsm[wormEv][wormSt]).action_routine(this);
}
