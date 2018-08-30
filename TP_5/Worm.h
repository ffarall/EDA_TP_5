#pragma once
class Worm
{
public:
	Worm();
	void update(Worm * wArray[], int wormCount);

private:
	wormStates_n currentState; // START_MOVING, MOVING, STOP_MOVING, RESTING, JUMP
	posType pos;
	const double speed = WORM_SPEED;
	const double g = WORM_GRAVITY;
	const double angle = PI / 3;
	bool lookingRight;
	uint frameCounter;
};

