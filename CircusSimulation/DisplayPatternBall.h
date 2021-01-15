#ifndef DISPLAY_PATTERN_BALL_H
#define DISPLAY_PATTERN_BALL_H

class DisplayPatternBall
{

private:

	PatternBallState state;
	unsigned int throw_value;
	unsigned int action_value;
	unsigned int beats_elapsed;

	void Ball_StateRemoved();

public:

	DisplayPatternBall();
	~DisplayPatternBall();

	void IncreaseBeatsElapsed();
	void AssignNewThrow(const unsigned int &, const unsigned int &);

	unsigned int GetBeatsElapsed() const;
	PatternBallState GetState() const;
	unsigned int GetThrowValue() const;
	unsigned int GetActionValue() const;

	friend class DisplayPatternHandler;

};

#endif
