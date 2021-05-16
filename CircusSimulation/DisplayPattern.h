#ifndef DISPLAY_PATTERN_H
#define DISPLAY_PATTERN_H

#include "stdafx.h"

#include "Struct.h"

class DisplayPattern
{

private:

	bool is_valid;

	unsigned int * indices_balls;
	unsigned int * indices_actions;

	unsigned int mapping_length;
	unsigned int mapping_length_initial;

	unsigned int ** mapping_throws;
	unsigned int ** * mapping_balls;
	unsigned int ** * mapping_actions;

	unsigned int num_balls;
	unsigned int num_actions;

	unsigned int pattern_max_throw_value;

public:

	DisplayPattern(const SiteswapPattern&);
	~DisplayPattern();

	bool IsValid() const;
	unsigned int GetRepeatingLength() const;
	unsigned int GetTotalLength() const;
	const unsigned int* GetThrow(const unsigned int& indexThrow, const unsigned int& indexAction) const;
	const unsigned int* GetBall(const unsigned int& indexThrow, const unsigned int& indexAction) const;
	const unsigned int* GetAction(const unsigned int& indexThrow, const unsigned int& indexAction) const;
	unsigned int GetNumberBalls() const;
	unsigned int GetNumberActions() const;
	unsigned int GetMaxThrow() const;

};

#endif
