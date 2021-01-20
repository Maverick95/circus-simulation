#include "DisplayPattern.h"



DisplayPattern::DisplayPattern(const SiteswapPattern & sp)
	:
	is_valid(StructFunctions::IsSiteswapPatternValid(sp)),
	indices_balls(NULL),
	indices_actions(NULL),
	mapping_length(0),
	mapping_length_initial(0),
	mapping_throws(NULL),
	mapping_balls(NULL),
	mapping_actions(NULL),
	num_balls(0),
	num_actions(0),
	pattern_max_throw_value(0)
{
	if (is_valid)
	{
		// Copy num_balls.

		num_balls = sp.num_balls;

		// Copy mapping_length_initial.

		mapping_length_initial = sp.throws.size();

		// Initialize indices_balls.

		indices_balls = new unsigned int[num_balls];

		for (unsigned int i = 0; i < num_balls; i++)
		{
			indices_balls[i] = i;
		}

		// Initialize num_actions and indices_actions (vanilla siteswap - simple case).
		
		num_actions = 1;
		indices_actions = new unsigned int[1];
		indices_actions[0] = 0;

		// Get the max pattern throw value.

		for (auto i = sp.throws.begin(); i != sp.throws.end(); i++)
		{
			if (i->state_transfer_throw > pattern_max_throw_value)
			{
				pattern_max_throw_value = i->state_transfer_throw;
			}
		}

		// Code below has been copied from the window function.

		const std::deque<SiteswapGraphConnection> & pf = sp.throws;
		std::deque<unsigned int> cycle_lengths;
		unsigned int cycle_lengths_lcm_counter = 0;

		bool * throw_accessed = new bool[pf.size()];
		for (unsigned int i = 0; i < pf.size(); i++)
		{
			throw_accessed[i] = false;
		}

		// Obtain cycle lengths.

		for (unsigned int i = 0; i < pf.size(); i++)
		{
			if (!throw_accessed[i])
			{
				// New set of throws to loop through.
				unsigned int cycle_length = 0;
				unsigned int j = i;

				while (!throw_accessed[j])
				{
					throw_accessed[j] = true;
					j += pf[j].state_transfer_throw;
					cycle_length += j / pf.size();
					j %= pf.size();
				}

				cycle_lengths.push_back(cycle_length);
				if (cycle_length > 1)
				{
					cycle_lengths_lcm_counter++;
				}
			}
		}

		delete[] throw_accessed;

		// Obtain lowest common multiple.

		unsigned int return_lcm = 1;

		while (cycle_lengths_lcm_counter > 0)
		{
			for (unsigned int i = 0; i < cycle_lengths.size(); i++)
			{
				if (cycle_lengths[i] > 1)
				{
					unsigned int divisor = 2;
					while (cycle_lengths[i] % divisor > 0) { divisor++; }

					// Apply divisor to integer plus all following integers where possible.

					return_lcm *= divisor;
					cycle_lengths[i] /= divisor;
					if (cycle_lengths[i] == 1) { cycle_lengths_lcm_counter--; }

					for (unsigned int j = i + 1; j < cycle_lengths.size(); j++)
					{
						if (cycle_lengths[j] % divisor == 0)
						{
							cycle_lengths[j] /= divisor;
							if (cycle_lengths[j] == 1) { cycle_lengths_lcm_counter--; }
						}
					}

					break;
				}
			}
		}

		// We've return the lowest common multiple, now we can compute the mappings.

		mapping_length = pf.size() * return_lcm;

		mapping_throws = new unsigned int*[mapping_length];
		mapping_balls = new unsigned int**[mapping_length];
		mapping_actions = new unsigned int**[mapping_length];

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			mapping_throws[i] = new unsigned int[1];

			mapping_balls[i] = new unsigned int*[1];
			mapping_balls[i][0] = NULL;

			mapping_actions[i] = new unsigned int*[1];
			mapping_actions[i][0] = NULL;
		}

		// Set up mapping_throws.

		unsigned int mapping_throws_counter = 0;

		for (unsigned int i = 0; i < return_lcm; i++)
		{
			for (auto j = pf.begin(); j != pf.end(); j++)
			{
				mapping_throws[mapping_throws_counter][0] = j->state_transfer_throw;
				mapping_throws_counter++;
			}
		}

		// Set up mapping_balls.

		unsigned int mapping_ball_index = 0;

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			if (mapping_balls[i][0] == NULL && mapping_throws[i][0] > 0)
			{
				for (unsigned int j = i; j < mapping_length; j += mapping_throws[j][0])
				{
					mapping_balls[j][0] = indices_balls + mapping_ball_index;
				}

				mapping_ball_index++;
			}
		}

		// Set up mapping_actions (vanilla siteswap - simple case).

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			if (mapping_throws[i][0] > 0)
			{
				mapping_actions[i][0] = indices_actions;
			}
		}
	}
}

DisplayPattern::~DisplayPattern()
{
	if (is_valid)
	{
		delete[] indices_balls;
		delete[] indices_actions;

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			delete[] mapping_throws[i];
			delete[] mapping_balls[i];
			delete[] mapping_actions[i];
		}

		delete[] mapping_throws;
		delete[] mapping_balls;
		delete[] mapping_actions;
	}
}

bool DisplayPattern::IsValid() const
{
	return is_valid;
}

unsigned int DisplayPattern::GetRepeatingLength() const
{
	return mapping_length_initial;
}

unsigned int DisplayPattern::GetTotalLength() const
{
	return mapping_length;
}

const unsigned int * DisplayPattern::GetThrow(const unsigned int & i, const unsigned int & j) const
{
	const unsigned int * return_value = NULL;

	if (i < mapping_length && j < num_actions)
	{
		return_value = &(mapping_throws[i][j]);
	}

	return return_value;
}

const unsigned int * DisplayPattern::GetBall(const unsigned int & i, const unsigned int & j) const
{
	const unsigned int * return_value = NULL;

	if (i < mapping_length && j < num_actions)
	{
		return_value = mapping_balls[i][j];
	}

	return return_value;
}

const unsigned int * DisplayPattern::GetAction(const unsigned int & i, const unsigned int & j) const
{
	const unsigned int * return_value = NULL;

	if (i < mapping_length && j < num_actions)
	{
		return_value = mapping_actions[i][j];
	}

	return return_value;
}

unsigned int DisplayPattern::GetNumberBalls() const
{
	return num_balls;
}

unsigned int DisplayPattern::GetNumberActions() const
{
	return num_actions;
}

unsigned int DisplayPattern::GetMaxThrow() const
{
	return pattern_max_throw_value;
}
