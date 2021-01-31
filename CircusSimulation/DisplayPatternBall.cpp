#include "DisplayPatternBall.h"



void DisplayPatternBall::Ball_StateRemoved()
{
	state = STATE_NONE;
	throw_value = 0;
	action_value = 0;
	beats_elapsed = 0;
}

DisplayPatternBall::DisplayPatternBall()
	:
	state(STATE_NONE),
	throw_value(0),
	action_value(0),
	beats_elapsed(0)
{

}

DisplayPatternBall::~DisplayPatternBall()
{

}

void DisplayPatternBall::IncreaseBeatsElapsed()
{
	switch (state)
	{

	case STATE_BEING_THROWN:

		beats_elapsed++;

		if (beats_elapsed == throw_value)
		{
			Ball_StateRemoved();
		}

		break;

	}
}

void DisplayPatternBall::AssignNewThrow(const unsigned int & t, const unsigned int & a)
{
	state = STATE_BEING_THROWN;
	throw_value = t;
	action_value = a;
}


unsigned int DisplayPatternBall::GetBeatsElapsed() const
{
	return beats_elapsed;
}

PatternBallState DisplayPatternBall::GetState() const
{
	return state;
}

unsigned int DisplayPatternBall::GetThrowValue() const
{
	return throw_value;
}

unsigned int DisplayPatternBall::GetActionValue() const
{
	return action_value;
}
