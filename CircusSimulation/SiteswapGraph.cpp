#include <chrono>
#include <queue>
#include <random>

#include "Enum.h"
#include "Functions.h"
#include "Settings.h"
#include "SiteswapGraphShortestPathChain.h"

#include "SiteswapGraph.h"
#include "SiteswapGraphMultiActionFunctions.h"



static unsigned int SETTINGS_MAX_THROW = Settings::ThrowHeight_Maximum();



void AddPaths_Recursive(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::deque<SiteswapGraphConnection>& p_current,
	std::set<SiteswapState>& a,
	const SiteswapState& s_current,
	const SiteswapState& s_end,
	const unsigned int n);

void AddPaths(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::set<SiteswapState>& a,
	const SiteswapState& s_begin,
	const SiteswapState& s_end,
	const unsigned int& n);

bool IsDestinationExtensionOfSource(const UIntStore& source, const UIntStore& destination);



bool IsDestinationExtensionOfSource(const UIntStore& source, const UIntStore& destination)
{
	if (source.Size() != destination.Size())
	{
		return false;
	}

	for (unsigned int i = 0U; i < source.Size(); i++)
	{
		if (source[i] & ~destination[i])
		{
			return false;
		}
	}

	return true;
}

bool SiteswapGraph::DoesPathExist(const UIntStore& state_start, const UIntStore& state_end, const unsigned int& max_steps)
{
	if (state_start == state_end)
	{
		return true;
	}

	if (state_start.Bits() == state_end.Bits())
	{
		UIntStore state_start_copy = state_start;

		for (unsigned int i = 0U; i < max_steps; i++)
		{
			state_start_copy.Next();

			if (IsDestinationExtensionOfSource(state_start_copy, state_end))
			{
				return true;
			}
		}

		return false;
	}

	return false;
}

void AddPaths_Recursive(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::deque<SiteswapGraphConnection>& p_current,
	std::set<SiteswapState>& a,
	const SiteswapState& s_current,
	const SiteswapState& s_end,
	const unsigned int n)
{
	auto connections = SiteswapGraphMultiAction::NextStates(s_current, SETTINGS_MAX_THROW);

	if (n == 1)
	{
		for (auto i = connections.begin(); i != connections.end(); i++)
		{
			if (i->state_end == s_end)
			{
				p_current.push_back(*i);
				p.push_back(p_current);
				p_current.pop_back();
			}
		}
	}
	else
	{
		for (auto i = connections.begin(); i != connections.end(); i++)
		{
			if (SiteswapGraph::DoesPathExist(i->state_end, s_end, n - 1) && a.find(i->state_end) == a.end())
			{
				p_current.push_back(*i);
				a.insert(i->state_end);
				AddPaths_Recursive(p, p_current, a, i->state_end, s_end, n - 1);
				p_current.pop_back();
				a.erase(i->state_end);
			}
		}
	}
}

void AddPaths(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::set<SiteswapState>& a,
	const SiteswapState& s_begin,
	const SiteswapState& s_end,
	const unsigned int& n)
{
	if (a.find(s_begin) == a.end() &&
		a.find(s_end) == a.end() &&
		SiteswapGraph::DoesPathExist(s_begin, s_end, n))
	{
		a.insert(s_begin);
		AddPaths_Recursive(p, std::deque<SiteswapGraphConnection>(), a, s_begin, s_end, n);
		a.erase(s_begin);
	}
}

SiteswapPattern* SiteswapGraph::GetRandomPattern(const unsigned int& b, const unsigned int& t, const unsigned int& max_throw)
{
	SETTINGS_MAX_THROW = max_throw > Settings::ThrowHeight_Maximum() ? Settings::ThrowHeight_Maximum() : max_throw;

	if (b > SETTINGS_MAX_THROW) { return NULL; }

	std::set<SiteswapState> a;
	std::deque<std::deque<SiteswapGraphConnection>> p;

	auto states = SiteswapGraphMultiAction::AllStates(1U, SETTINGS_MAX_THROW, b);

	for (auto i = states.begin(); i != states.end(); i++)
	{
		if (a.find(*i) == a.end())
		{
			// New condition - use state if at least 1 bit in the Next().

			AddPaths(p, a, *i, *i, t);
			
			a.insert(*i);
			
			/*

			for (unsigned int j = 1U; (st << j) <= max_state; j++)
			{
				a[st << j] = false;
			}
			*/
		}
	}

	if (p.size() == 0)
	{
		return NULL;
	}

	return new SiteswapPattern({
			b, 1U,
			*(
			p.begin() +
			std::uniform_int_distribution<unsigned int>(0, p.size() - 1)(
				std::default_random_engine(
					std::chrono::system_clock::now().time_since_epoch().count()))
			) });
}

std::set<SiteswapPattern>* SiteswapGraph::GetPatterns(const unsigned int& b, const unsigned int& t, const unsigned int& max_throw)
{
	SETTINGS_MAX_THROW = max_throw > Settings::ThrowHeight_Maximum() ? Settings::ThrowHeight_Maximum() : max_throw;

	if (b > SETTINGS_MAX_THROW) { return NULL; }

	std::set<SiteswapState> a;
	std::deque<std::deque<SiteswapGraphConnection>> p;

	auto states = SiteswapGraphMultiAction::AllStates(1U, SETTINGS_MAX_THROW, b);

	for (auto i = states.begin(); i != states.end(); i++)
	{
		if (a.find(*i) == a.end())
		{
			// New condition - use state if at least 1 bit in the Next().

			AddPaths(p, a, *i, *i, t);

			a.insert(*i);

			/*

			for (unsigned int j = 1U; (st << j) <= max_state; j++)
			{
				a[st << j] = false;
			}
			*/
		}
	}

	if (p.size() == 0)
	{
		return NULL;
	}

	std::set<SiteswapPattern>* patterns = new std::set<SiteswapPattern>();
	
	for (auto i = p.begin(); i != p.end(); i++)
	{
		patterns->insert({ b, 1U, *i }); 
	}

	return patterns;
}

