#include "Struct.h"
#include "Functions.h"



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
	// Base properties need to be valid.

	if (sp.num_balls > 0U && !sp.throws.empty())
	{
		// Check that the first throw is a valid state given num_balls.

		if (sp.num_balls == sp.throws[0U].state_begin.Bits())
		{
			for (unsigned int i = 0U; i < sp.throws.size(); i++)
			{
				const SiteswapState
					&sp_state_begin_current = sp.throws[i].state_begin,
					&sp_state_end_current = sp.throws[i].state_end,
					&sp_state_begin_next = sp.throws[i == sp.throws.size() - 1U ? 0U : i + 1U].state_begin;

				const SiteswapThrow
					&sp_throw_current = sp.throws[i].state_transfer_throw();

				// End state is the product of begin state and the throw.

				if (!IsThrowValid(sp_state_begin_current, sp_state_end_current, sp_throw_current) ||
					(sp_state_end_current != sp_state_begin_next))
				{
					return false;
				}

			}

			return true;
		}
	}

	return false;
}

bool StructFunctions::IsThrowValid(const SiteswapState& s1, const SiteswapState& s2, const SiteswapThrow& t)
{
	// To fill out.
	return true;
}
