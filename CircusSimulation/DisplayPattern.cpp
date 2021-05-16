#include "DisplayPattern.h"
#include "Functions.h"



DisplayPattern::DisplayPattern(const SiteswapPattern& sp)
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
		// Copy key variables.

		num_balls = sp.num_balls;
		num_actions = sp.num_actions;
		mapping_length_initial = sp.throws.size();

		// Initialize indices_ vectors.

		indices_balls = new unsigned int[num_balls];
		indices_actions = new unsigned int[num_actions];

		for (unsigned int i = 0U; i < num_balls; i++)
		{
			indices_balls[i] = i;
		}

		for (unsigned int i = 0U; i < num_actions; i++)
		{
			indices_actions[i] = i;
		}

		// Get the max pattern throw value.

		for (auto i = sp.throws.begin(); i != sp.throws.end(); i++)
		{
			for (auto j = i->state_transfer.begin(); j != i->state_transfer.end(); j++)
			{
				if (j->state_transfer_throw > pattern_max_throw_value)
				{
					pattern_max_throw_value = j->state_transfer_throw;
				}
			}
		}

		// Code below has been copied from the window function.

		// Isolate the groups of throws in the pattern that are "linked" by
		// the same ball being used, and for each, calculate the number of
		// cycles of the pattern it takes to iterate through the group.
	
		const std::deque<SiteswapGraphConnection> & pf = sp.throws;
		std::vector<unsigned int> cycle_lengths;
		unsigned int cycle_lengths_lcm_counter = 0;

		bool ** throw_accessed = new bool*[mapping_length_initial];

		for (unsigned int i = 0U; i < mapping_length_initial; i++)
		{
			throw_accessed[i] = new bool[num_actions];
			for (unsigned int j = 0U; j < num_actions; j++)
			{
				throw_accessed[i][j] = false;
			}
		}

		for (unsigned int i = 0U; i < mapping_length_initial; i++)
		{
			for (unsigned int j = 0U; j < num_actions; j++)
			{
				if (!throw_accessed[i][j])
				{
					// New set of throws to loop through.
					unsigned int cycle_length = 0;
					unsigned int i2 = i, j2 = j;

					while (!throw_accessed[i2][j2])
					{
						throw_accessed[i2][j2] = true;

						// This should be better optimised, however it proves difficult at the moment.
						// Reason is that actions are only stored if they occur.
						// So actions < possible number of actions, therefore they can't be indexed.

						for (auto k = pf[i2].state_transfer.begin(); k != pf[i2].state_transfer.end(); k++)
						{
							if (k->index_state_source == j2)
							{
								i2 += k->state_transfer_throw;
								j2 = k->index_state_destination;
								break;
							}
						}

						cycle_length += i2 / pf.size();
						i2 %= pf.size();
					}

					if (cycle_length > 0U)
					{
						cycle_lengths.push_back(cycle_length);
						if (cycle_length > 1)
						{
							cycle_lengths_lcm_counter++;
						}
					}
				}
			}
		}

		for (unsigned int i = 0U; i < mapping_length_initial; i++)
		{
			delete[] throw_accessed[i];
		}

		delete[] throw_accessed;

		// Obtain the lowest common multiple, this is the number of cycles before the 
		// whole pattern functionally repeats itself.

		auto return_lcm = Functions::LowestCommonMultiple(cycle_lengths);

		// Use the LCM to compute all the mappings required.

		mapping_length = pf.size() * return_lcm;

		mapping_throws = new unsigned int*[mapping_length];
		mapping_balls = new unsigned int**[mapping_length];
		mapping_actions = new unsigned int**[mapping_length];

		for (unsigned int i = 0U; i < mapping_length; i++)
		{
			mapping_throws[i] = new unsigned int[num_actions];
			mapping_balls[i] = new unsigned int*[num_actions];
			mapping_actions[i] = new unsigned int*[num_actions];

			for (unsigned int j = 0U; j < num_actions; j++)
			{
				mapping_throws[i][j] = 0U;
				mapping_actions[i][j] = NULL;
				mapping_balls[i][j] = NULL;
			}
		}

		// Set up mapping_throws and mapping actions.

		unsigned int mapping_counter = 0;

		for (unsigned int i = 0; i < return_lcm; i++)
		{
			for (auto j = pf.begin(); j != pf.end(); j++)
			{
				for (auto k = j->state_transfer.begin(); k != j->state_transfer.end(); k++)
				{
					mapping_throws[mapping_counter][k->index_state_source] = k->state_transfer_throw;
					mapping_actions[mapping_counter][k->index_state_source] = indices_actions + k->index_state_destination;
				}

				mapping_counter++;
			}
		}

		// Set up mapping_balls.

		unsigned int mapping_ball_index = 0;

		for (unsigned int i = 0U; i < mapping_length; i++)
		{
			for (unsigned int k = 0U; k < num_actions; k++)
			{
				if (mapping_balls[i][k] == NULL && mapping_throws[i][k] > 0U)
				{
					unsigned int k_copy = k;
					for (unsigned int j = i; j < mapping_length; j += mapping_throws[j][k_copy])
					{
						mapping_balls[j][k_copy] = indices_balls + mapping_ball_index;
						k_copy = *(mapping_actions[j][k_copy]);
					}

					mapping_ball_index++;
				}
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

const unsigned int* DisplayPattern::GetThrow(const unsigned int& indexThrow, const unsigned int& indexAction) const
{
	const unsigned int * return_value = NULL;

	if (indexThrow < mapping_length && indexAction < num_actions)
	{
		return_value = &(mapping_throws[indexThrow][indexAction]);
	}

	return return_value;
}

const unsigned int* DisplayPattern::GetBall(const unsigned int& indexThrow, const unsigned int& indexAction) const
{
	const unsigned int * return_value = NULL;

	if (indexThrow < mapping_length && indexAction < num_actions)
	{
		return_value = mapping_balls[indexThrow][indexAction];
	}

	return return_value;
}

const unsigned int* DisplayPattern::GetAction(const unsigned int& indexThrow, const unsigned int& indexAction) const
{
	const unsigned int * return_value = NULL;

	if (indexThrow < mapping_length && indexAction < num_actions)
	{
		return_value = mapping_actions[indexThrow][indexAction];
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
