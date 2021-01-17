#include "stdafx.h"

bool SiteswapPattern::operator<(const SiteswapPattern& sp) const
{
	if (num_balls < sp.num_balls || throws.size() < sp.throws.size())
	{
		return true;
	}

	if (throws.size() == sp.throws.size())
	{
		for (unsigned int i = 0U; i < throws.size(); i++)
		{
			if (throws[i].state_transfer_throw < sp.throws[i].state_transfer_throw)
			{
				return true;
			}
			else if (throws[i].state_transfer_throw > sp.throws[i].state_transfer_throw)
			{
				return false;
			}
		}
	}

	return false;
}

bool StructFunctions::IsSiteswapPatternValid(const SiteswapPattern & sp)
{
	bool return_value = false;

	// Base properties need to be valid.

	if (sp.num_balls > 0 && !sp.throws.empty())
	{
		// Check that the first throw is a valid state given num_balls.

		const unsigned int & sp_state_begin = sp.throws[0].state_begin;
		unsigned int sp_state_begin_lp = sp_state_begin;
		unsigned int sp_state_begin_lp_balls = 0;

		for (unsigned int i = 0; sp_state_begin_lp > 0; i++)
		{
			if ((sp_state_begin & (1u << i)) > 0)
			{
				sp_state_begin_lp_balls++;
				sp_state_begin_lp -= (1u << i);
			}
		}

		if (sp.num_balls == sp_state_begin_lp_balls)
		{
			// Loop through each throw and check that the throws map the beginning state to the end state.

			bool lp_valid = true;

			for (unsigned int i = 0; i < sp.throws.size(); i++)
			{
				bool lp_break = true;

				const unsigned int & sp_state_begin_current = sp.throws[i].state_begin;
				const unsigned int & sp_state_end_current = sp.throws[i].state_end;
				const unsigned int & sp_throw_current = sp.throws[i].state_transfer_throw;
				const unsigned int & sp_state_begin_next = sp.throws[i == sp.throws.size() - 1 ? 0 : i + 1].state_begin;

				// End state is the product of begin state and the throw.

				if ((sp_state_begin_current & (1u << sp_throw_current)) == 0)
				{
					if (sp_state_end_current == ((sp_state_begin_current | (1u << sp_throw_current)) >> 1))
					{
						// End state and next begin states match.

						if (sp_state_end_current == sp_state_begin_next)
						{
							lp_break = false;
						}
					}
				}

				if (lp_break)
				{
					lp_valid = false;
					break;
				}
			}

			if (lp_valid)
			{
				return_value = true;
			}
		}
	}

	return return_value;
}
