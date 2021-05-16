#include <chrono>
#include <queue>
#include <random>
#include <unordered_set>

#include "Enum.h"
#include "Functions.h"
#include "Settings.h"

#include "SiteswapGraph.h"
#include "SiteswapGraphMultiAction.h"



void AddPaths_Recursive(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::deque<SiteswapGraphConnection>& p_current,
	std::unordered_set<std::string>& a,
	const SiteswapState& s_current,
	const SiteswapState& s_end,
	const unsigned int n,
	const unsigned int& maxThrow);

void AddPaths(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::unordered_set<std::string>& a,
	const SiteswapState& s_begin,
	const SiteswapState& s_end,
	const unsigned int& n,
	const unsigned int& maxThrow);



void AddPaths_Recursive(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::deque<SiteswapGraphConnection>& p_current,
	std::unordered_set<std::string>& a,
	const SiteswapState& s_current,
	const SiteswapState& s_end,
	const unsigned int n,
	const unsigned int& maxThrow)
{
	std::forward_list<SiteswapGraphConnection> connections;
	SiteswapGraphMultiAction::StoreNextStates(connections, s_current, maxThrow);

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
			std::string hash = i->state_end;
			if (SiteswapGraphMultiAction::DoesPathExist(i->state_end, s_end, n - 1) && a.find(hash) == a.end())
			{
				p_current.push_back(*i);
				a.insert(hash);
				AddPaths_Recursive(p, p_current, a, i->state_end, s_end, n - 1, maxThrow);
				p_current.pop_back();
				a.erase(hash);
			}
		}
	}
}

void AddPaths(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::unordered_set<std::string>& a,
	const SiteswapState& s_begin,
	const SiteswapState& s_end,
	const unsigned int& n,
	const unsigned int& maxThrow)
{
	std::string
		hash_begin = s_begin,
		hash_end = s_end;

	if (a.find(hash_begin) == a.end() &&
		a.find(hash_end) == a.end() &&
		SiteswapGraphMultiAction::DoesPathExist(s_begin, s_end, n))
	{
		a.insert(hash_begin);
		AddPaths_Recursive(p, std::deque<SiteswapGraphConnection>(), a, s_begin, s_end, n, maxThrow);
		a.erase(hash_begin);
	}
}

SiteswapPattern* SiteswapGraph::GetRandomPattern(
	const unsigned int& numberBalls,
	const unsigned int& numberActions,
	const unsigned int& numberThrows,
	unsigned int maxThrow)
{
	const unsigned int maxThrowSettings = Settings::ThrowHeight_Maximum();

	if (maxThrow > maxThrowSettings)
	{
		maxThrow = maxThrowSettings;
	}

	if (numberBalls == 0U ||
		numberBalls > (maxThrow * numberActions) ||
		numberActions == 0U ||
		numberThrows == 0U)
	{
		return NULL;
	}

	std::unordered_set<std::string> a;
	std::deque<std::deque<SiteswapGraphConnection>> p;
	std::vector<UIntStore> states;
	SiteswapGraphMultiAction::StoreValidBeginStates(states, numberActions, maxThrow, numberBalls);

	for (auto i = states.begin(); i != states.end(); i++)
	{
		if (a.find(*i) == a.end())
		{
			AddPaths(p, a, *i, *i, numberThrows, maxThrow);
			do { a.insert(*i); }
			while (i->Previous(maxThrow));
		}
	}

	if (p.size() == 0)
	{
		return NULL;
	}

	return new SiteswapPattern({
			numberBalls, numberActions,
			*(
			p.begin() +
			std::uniform_int_distribution<unsigned int>(0, p.size() - 1)(
				std::default_random_engine(
					std::chrono::system_clock::now().time_since_epoch().count()))
			) });
}

std::set<SiteswapPattern>* SiteswapGraph::GetPatterns(
	const unsigned int& numberBalls,
	const unsigned int& numberActions,
	const unsigned int& numberThrows,
	unsigned int maxThrow)
{
	const unsigned int maxThrowSettings = Settings::ThrowHeight_Maximum();

	if (maxThrow > maxThrowSettings)
	{
		maxThrow = maxThrowSettings;
	}

	if (numberBalls == 0U ||
		numberBalls > (maxThrow * numberActions) ||
		numberActions == 0U ||
		numberThrows == 0U)
	{
		return NULL;
	}

	std::unordered_set<std::string> a;
	std::deque<std::deque<SiteswapGraphConnection>> p;
	std::vector<UIntStore> states;
	SiteswapGraphMultiAction::StoreValidBeginStates(states, numberActions, maxThrow, numberBalls);

	for (auto i = states.begin(); i != states.end(); i++)
	{
		if (a.find(*i) == a.end())
		{
			AddPaths(p, a, *i, *i, numberThrows, maxThrow);
			do { a.insert(*i); } while (i->Previous(maxThrow));
		}
	}

	if (p.size() == 0)
	{
		return NULL;
	}

	std::set<SiteswapPattern>* patterns = new std::set<SiteswapPattern>();
	
	for (auto i = p.begin(); i != p.end(); i++)
	{
		patterns->insert({ numberBalls, numberActions, *i });
	}

	return patterns;
}

