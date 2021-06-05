#include "Struct.h"
#include "Functions.h"



bool operator==(const SiteswapGraphConnection& sgc1, const SiteswapGraphConnection& sgc2)
{
	if (sgc1.state_begin == sgc2.state_begin &&
		sgc1.state_end == sgc2.state_end &&
		sgc1.state_transfer.size() == sgc2.state_transfer.size())
	{
		for (unsigned int i = 0U; i < sgc1.state_transfer.size(); i++)
		{
			if (sgc1.state_transfer[i] != sgc2.state_transfer[i])
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool operator!=(const SiteswapGraphConnection& sgc1, const SiteswapGraphConnection& sgc2)
{
	return !(sgc1 == sgc2);
}

bool operator<(const SiteswapPattern& sp1, const SiteswapPattern& sp2)
{
	if (sp1.num_balls != sp2.num_balls)
	{
		return sp1.num_balls < sp2.num_balls;
	}

	if (sp1.num_actions != sp2.num_actions)
	{
		return sp1.num_actions < sp2.num_actions;
	}

	if (sp1.throws.size() != sp2.throws.size())
	{
		return sp1.throws.size() < sp2.throws.size();
	}

	for (unsigned int i = 0U; i < sp1.throws.size(); i++)
	{
		if (sp1.throws[i].state_begin != sp2.throws[i].state_begin)
		{
			return sp1.throws[i].state_begin < sp2.throws[i].state_begin;
		}

		if (sp1.throws[i].state_end != sp2.throws[i].state_end)
		{
			return sp1.throws[i].state_end < sp2.throws[i].state_end;
		}

		// Currently no distinction made for different state_transfer,
		// these are assumed to be the default given a state_begin / state_end.
	}

	return false;
}

bool operator==(const SiteswapPattern& sp1, const SiteswapPattern& sp2)
{
	if (sp1.num_balls != sp2.num_balls || sp1.num_actions != sp2.num_actions || sp1.throws.size() != sp2.throws.size())
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
	os << "Actions : " << sp.num_actions << std::endl;
	for (auto i = sp.throws.begin(); i != sp.throws.end(); i++)
	{
		os << "From : " << i->state_begin << " - To : " << i->state_end << " - By : [";
		for (auto j = i->state_transfer.begin(); j != i->state_transfer.end(); j++)
		{
			os << *j << ",";
		}
		os << "]" << std::endl;
	}

	return os;
}

bool StructFunctions::IsSiteswapPatternValid(const SiteswapPattern& sp)
{
	// To fill out.

	/*
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
	*/

	return true;
}

bool StructFunctions::IsThrowValid(const SiteswapState& s1, const SiteswapState& s2, const SiteswapThrow& t)
{
	// To fill out.

	return true;
}

std::string StructFunctions::GetSiteswapPatternLookupLabel(const SiteswapPattern& pattern)
{
	switch (pattern.num_actions)
	{
	case 1U:
	{
		std::string result;

		for (auto i = pattern.throws.begin(); i != pattern.throws.end(); i++)
		{
			const unsigned int nextThrow =
				i->state_transfer.size() == 0U ?
				0U :
				i->state_transfer[0].state_transfer_throw;

			result += std::to_string(nextThrow) + " ";
		}

		if (result.length() > 0U)
		{
			result.erase(result.length() - 1U);
		}

		return result;
	}
	case 2U:
	{
		std::string result;

		for (auto i = pattern.throws.begin(); i != pattern.throws.end(); i++)
		{
			unsigned int throws[2] = { 0U, 0U };
			bool transfer[2] = { false, false };

			for (auto j = i->state_transfer.begin(); j != i->state_transfer.end(); j++)
			{
				throws[j->index_state_source] = 2 * j->state_transfer_throw;
				transfer[j->index_state_source] = j->index_state_source != j->index_state_destination;
			}

			result += "[";
			for (unsigned int j = 0U; j < 2U; j++)
			{
				result += std::to_string(throws[j]) +
					(transfer[j] ? "x" : "") +
					(j == 0U ? " " : "");
			}
			result += "] ";
		}

		if (result.length() > 0U)
		{
			result.erase(result.length() - 1U);
		}

		return result;
	}
	}

	return "N/A";
}
