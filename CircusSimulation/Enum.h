#ifndef ENUM_H
#define ENUM_H

enum PatternBallState
{
	STATE_NONE,
	STATE_BEING_THROWN
};

enum PatternHand
{
	HAND_NONE,
	HAND_LEFT,
	HAND_RIGHT
};

enum DisplayPatternHandlerState
{
	PH_STATE_EMPTY,
	PH_STATE_STOP,
	PH_STATE_PLAY,
	PH_STATE_PAUSE,
	PH_STATE_PAUSE_TRANSIT,
	PH_STATE_SINGLE_BEAT_FORWARD
};

enum DisplayPatternHandlerSpeed
{
	SPD_HALF,
	SPD_NORMAL,
	SPD_DOUBLE
};

enum DisplayPatternHandlerSpeedChange
{
	SPD_CHG_NONE,
	SPD_CHG_HALF,
	SPD_CHG_NORMAL,
	SPD_CHG_DOUBLE
};

#endif
