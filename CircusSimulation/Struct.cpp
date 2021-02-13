#include "Struct.h"

SiteswapState::SiteswapState(const unsigned int& s, const unsigned int* st) :
	states_size(s == 0U ? 1U : s),
	states(new unsigned int[states_size])
{
	for (unsigned int i = 0U; i < states_size; i++)
	{
		states[i] = (st == NULL ? 0U : st[i]);
	}
}

SiteswapState::SiteswapState(const unsigned int& st) :
	states_size(1U),
	states(new unsigned int[1U])
{
	states[0U] = st;
}

SiteswapState::~SiteswapState()
{
	delete[] states;
}

unsigned int SiteswapState::operator()() const
{
	return states[0U];
}

bool operator==(const SiteswapGraphConnection& sgc1, const SiteswapGraphConnection& sgc2)
{
	return (sgc1.state_begin == sgc2.state_begin &&
		sgc1.state_end == sgc2.state_end &&
		sgc1.state_transfer_throw == sgc2.state_transfer_throw);
}

bool operator!=(const SiteswapGraphConnection& sgc1, const SiteswapGraphConnection& sgc2)
{
	return !(sgc1 == sgc2);
}

bool operator<(const SiteswapPattern& sp1, const SiteswapPattern& sp2)
{
	if (sp1.num_balls < sp2.num_balls || sp1.throws.size() < sp2.throws.size())
	{
		return true;
	}

	if (sp1.throws.size() == sp2.throws.size())
	{
		for (unsigned int i = 0U; i < sp1.throws.size(); i++)
		{
			if (sp1.throws[i].state_transfer_throw < sp2.throws[i].state_transfer_throw)
			{
				return true;
			}
			else if (sp1.throws[i].state_transfer_throw > sp2.throws[i].state_transfer_throw)
			{
				return false;
			}
		}
	}

	return false;
}

bool operator==(const SiteswapPattern& sp1, const SiteswapPattern& sp2)
{
	if (sp1.num_balls != sp2.num_balls || sp1.throws.size() != sp2.throws.size())
	{
		return false;
	}

	for (unsigned int i = 0U; i < sp1.throws.size(); i++)
	{
		if (sp1.throws[i] != sp2.throws[i])
		{
			return false;
		}
	}

	return true;
}


bool operator!=(const SiteswapPattern& sp1, const SiteswapPattern& sp2)
{
	return !(sp1 == sp2);
}

std::ostream& operator<<(std::ostream& os, const SiteswapPattern& sp)
{
	os << "Balls : " << sp.num_balls << std::endl;
	for (auto i = sp.throws.begin(); i != sp.throws.end(); i++)
	{
		os << "From : " << i->state_begin << " - To : " << i->state_end << " - By : " << i->state_transfer_throw << std::endl;
	}

	return os;
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
