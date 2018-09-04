#include "Worm.h"
#include <cmath>

using namespace std;

#define WORM_FSM_STATES 7
#define WORM_FSM_EVENTS 6
#define NO_MOTION_FRAME_COUNT 8
#define	JUMPING_WORM_UP_FRAMES 6
#define FRAMES_PER_DX 14
#define SCENARIO_LEFT_EDGE 685
#define SCENARIO_RIGHT_EDGE	1170
#define SCENARIO_FLOOR 616
#define	WORM_MOVE_DIF 9.0


Worm::Worm(): pos()
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
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

Worm::Worm(int x_, int y_, char ku, char kl, char kr): pos(x_, y_)
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
	keyUp = ku;
	keyRight = kr;
	keyLeft = kl;
}

Worm::Worm(int x_, int y_): pos(x_, y_)
{
	currentState = IDLE;
	lookingRight = true; // If more worms were to be added to the game, initializing with rand() would be advisable.
	frameCounter = 0;
}


Worm::~Worm()
{
}

/*			GETTERS			*/

Vector Worm::get_pos()
{
	return pos;
}

bool Worm::get_orientation()
{
	return lookingRight;
}

uint Worm::get_frameCounter()
{
	return frameCounter;
}

char Worm::get_event()
{
	return ev;
}

wormState_n Worm::get_currentState()
{
	return currentState;
}

double Worm::get_jumpSpeed()
{
	return jumpSpeed;
}

double Worm::get_gravity()
{
	return g;
}

double Worm::get_angle()
{
	return angle;
}

char Worm::get_keyUp()
{
	return keyUp;
}

char Worm::get_keyLeft()
{
	return keyLeft;
}

char Worm::get_keyRight()
{
	return keyRight;
}

/*			SETTERS			*/		

void Worm::set_pos(Vector pos_)
{
	pos.set_x(pos_.get_x());
	pos.set_y(pos_.get_y());
}

void Worm::set_pos(int x_, int y_)
{
	pos.set_x(x_);
	pos.set_y(y_);
}

void Worm::set_x(int x_)
{
	pos.set_x(x_);
}

void Worm::set_y(int y_)
{
	pos.set_y(y_);
}

void Worm::inc_x(int x_)
{
	pos.inc_x(x_);
}

void Worm::inc_y(int y_)
{
	pos.inc_y(y_);
}

void Worm::set_keys(char ku, char kl, char kr)
{
	keyUp = ku;
	keyRight = kr;
	keyLeft = kl;
}

void Worm::set_orientation(bool orient)
{
	lookingRight = orient;
}

void Worm::inc_frameCounter()
{
	frameCounter++;
}

void Worm::set_frameCounter(uint fc)
{
	frameCounter = fc;
}

void Worm::set_currentState(wormState_n st)
{
	currentState = st;
}


/* Internal function to interprete the event and turn it into a Worm event, easier to handle by the fsm */

wormEvent_n Worm::event_decoder(Event& ev_)
{
	ev = ev_.get_key_event_keycode();
	switch (ev_.get_event_type())
	{
	case POSSIBLE_WORM_MOVE: 
	{
		if (ev == keyLeft)
		{
			return KEY_MOVE_LEFT_DOWN;
		}
		else if (ev == keyRight)
		{
			return KEY_MOVE_RIGHT_DOWN;
		}
		else if (ev == keyUp)
		{
			return KEY_JUMP_DOWN;
		}
		else
		{
			return NOT_VALID;
		}
	} break;
	case POSSIBLE_WORM_STOP:
	{
		if (ev == keyLeft || ev == keyRight)
		{
			return KEY_MOVE_UP;
		}
		else
		{
			return NOT_VALID;
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
	/* Fsm table */
	const wormFsmCell_n wormFsm[WORM_FSM_EVENTS][WORM_FSM_STATES] =
	{ // START_MOVING,							MOVING,								STOP_MOVING,						IDLE,								START_JUMPING							JUMPING						LANDING	
		{{START_MOVING, no_act_routine},		{MOVING, no_act_routine},			{STOP_MOVING, no_act_routine},		{START_MOVING, turn_worm},			{START_JUMPING, no_act_routine},		{JUMPING, no_act_routine},	{LANDING, no_act_routine}},		// KEY_MOVE_RIGHT_DOWN
		{{START_MOVING, no_act_routine},		{MOVING, no_act_routine},			{STOP_MOVING, no_act_routine},		{START_MOVING, turn_worm},			{START_JUMPING, no_act_routine},		{JUMPING, no_act_routine},	{LANDING, no_act_routine}},		// KEY_MOVE_LEFT_DOWN
		{{IDLE, no_act_routine},				{STOP_MOVING, no_act_routine},		{STOP_MOVING, no_act_routine},		{IDLE, no_act_routine},				{START_JUMPING, no_act_routine},		{JUMPING, no_act_routine},	{LANDING, no_act_routine}},		// KEY_MOVE_UP
		{{START_MOVING, refresh_start_moving},	{MOVING, refresh_moving},			{STOP_MOVING, refresh_stop_moving},	{IDLE, no_act_routine},				{START_JUMPING, refresh_start_jumping},	{JUMPING, refresh_jumping},	{LANDING, refresh_landing}},	// NEW_FRAME
		{{START_JUMPING, start_jumping},		{START_JUMPING, start_jumping},		{START_JUMPING, start_jumping},		{START_JUMPING, start_jumping},		{START_JUMPING, no_act_routine},		{JUMPING, no_act_routine},	{LANDING, no_act_routine}},		// KEY_JUMP_DOWN
		{{START_MOVING, no_act_routine},		{MOVING, no_act_routine},			{STOP_MOVING, no_act_routine},		{IDLE, no_act_routine},				{START_JUMPING, no_act_routine},		{JUMPING, no_act_routine},	{LANDING, no_act_routine}}		// NOT_VALID
	};

	wormEvent_n wormEv = event_decoder(ev);
	wormState_n wormSt = currentState;
	currentState = wormFsm[wormEv][wormSt].nextState;
	(wormFsm[wormEv][wormSt]).action_routine(this);
}

void Worm::move()
{
	if (lookingRight)
	{
		pos.inc_x(WORM_MOVE_DIF);		
	}
	else
	{	
		pos.inc_x(-WORM_MOVE_DIF);
	}
}

void no_act_routine(void * worm_)
{
}

void turn_worm(void * worm_)
{
	Worm * worm = (Worm *) worm_;
	worm->set_frameCounter(0);	// Initializing frameCounter for movement.

	if (worm->get_event() == worm->get_keyRight() && !(worm->get_orientation()))		// If moving right but looking left, turn.
	{
		worm->set_orientation(true);
	}
	else if (worm->get_event() == worm->get_keyLeft() && worm->get_orientation())			// If moving left but looking right, turn.
	{
		worm->set_orientation(false);
	}
}

void refresh_start_moving(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->inc_frameCounter();

	if (worm->get_frameCounter() == NO_MOTION_FRAME_COUNT)		// After the moving warm-up, state changes to moving.
	{
		worm->set_currentState(MOVING);
	}
}

void refresh_moving(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->inc_frameCounter();

	switch (worm->get_frameCounter())							// Every 14 frames after the warm up, the worm moves 9 pixels in the corresponding way.
	{
	case (NO_MOTION_FRAME_COUNT + FRAMES_PER_DX): worm->move(); break;
	case (NO_MOTION_FRAME_COUNT + 2 * FRAMES_PER_DX): worm->move(); break;
	case (NO_MOTION_FRAME_COUNT + 3 * FRAMES_PER_DX):
	{
		worm->move();
		worm->set_frameCounter(NO_MOTION_FRAME_COUNT);			// After last movement, since key is still down, the movement is restarted AFTER the warm-up.
	} break;
	}

	if (worm->get_pos().get_x() < SCENARIO_LEFT_EDGE)			// If worm crosses the left edge, it gets pulled back into the allowed area.
	{
		worm->set_x(SCENARIO_LEFT_EDGE);
	}
	else if (worm->get_pos().get_x() > SCENARIO_RIGHT_EDGE)		// If worm crosses the right edge, it gets pulled back into the allowed area.
	{
		worm->set_x(SCENARIO_RIGHT_EDGE);
	}
}

void refresh_stop_moving(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->inc_frameCounter();

	switch (worm->get_frameCounter())					// After a key up event, worm stops moving ONLY after any movement cycle's been completed.
	{
	case (NO_MOTION_FRAME_COUNT + FRAMES_PER_DX): 
	case (NO_MOTION_FRAME_COUNT + 2 * FRAMES_PER_DX): 
	case (NO_MOTION_FRAME_COUNT + 3 * FRAMES_PER_DX):
	{
		worm->move();
		worm->set_currentState(IDLE);
		worm->set_frameCounter(NO_MOTION_FRAME_COUNT);
	} break;
	default: break;
	}
}

void start_jumping(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->set_frameCounter(0);			// Initializing frameCounter for jump.
}

void refresh_start_jumping(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->inc_frameCounter();

	if (worm->get_frameCounter() == NO_MOTION_FRAME_COUNT)		// After the moving warm-up, state changes to jumping.
	{
		worm->set_currentState(JUMPING);
	}
}

void refresh_landing(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->inc_frameCounter();

	if (worm->get_frameCounter() == JUMPING_WORM_UP_FRAMES)
	{
		worm->set_currentState(IDLE);			// If the worm finishes landing, goes back to resting.
		worm->set_frameCounter(0);
	}
}

void refresh_jumping(void * worm_)
{
	Worm * worm = (Worm *)worm_;
	worm->inc_frameCounter();

	double angle = worm->get_angle();
	double jumpSpeed = worm->get_jumpSpeed();
	double gravity = worm->get_gravity();

	if (worm->get_orientation())
	{
		worm->inc_x(jumpSpeed * cos(angle));
	}
	else
	{
		worm->inc_x(-jumpSpeed * cos(angle));
	}
	if (worm->get_pos().get_x() < SCENARIO_LEFT_EDGE)			// If worm crosses the left edge, it gets pulled back into the allowed area.
	{
		worm->set_x(SCENARIO_LEFT_EDGE);						
	}
	else if (worm->get_pos().get_x() > SCENARIO_RIGHT_EDGE)		// If worm crosses the right edge, it gets pulled back into the allowed area.
	{
		worm->set_x(SCENARIO_RIGHT_EDGE);
	}

	worm->set_y(SCENARIO_FLOOR - jumpSpeed * sin(angle) * worm->get_frameCounter() + (gravity / 2) * pow(worm->get_frameCounter(), 2));
	if (worm->get_pos().get_y() > SCENARIO_FLOOR)	// If worm crosses the floor, it gets pulled back to the right position.
	{
		worm->set_y(SCENARIO_FLOOR);
		worm->set_currentState(LANDING);			// If the worm got back to the floor, goes to LANDING state.
		worm->set_frameCounter(0);
	}
}