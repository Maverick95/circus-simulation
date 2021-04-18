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



std::map<unsigned int, unsigned int> * SiteswapGraph::PrimeFactorise(unsigned int n)
{
	std::map<unsigned int, unsigned int> * return_map = new std::map<unsigned int, unsigned int>;

	unsigned int divisor = 2;

	while (n > 1)
	{
		bool divisor_used = false;

		while (n % divisor == 0)
		{
			if (divisor_used)
			{
				(*return_map)[divisor] += 1;
			}
			else
			{
				(*return_map)[divisor] = 1;
				divisor_used = true;
			}

			n /= divisor;
		}

		divisor++;
	}

	return return_map;
}

void SiteswapGraph::PrimeFactorise_Multiply(std::map<unsigned int, unsigned int> * p1, std::map<unsigned int, unsigned int> * p2)
{
	for (auto i = p2->begin(); i != p2->end(); i++)
	{
		if (p1->find(i->first) != p1->end())
		{
			(*p1)[i->first] += i->second;
		}
		else
		{
			(*p1)[i->first] = i->second;
		}
	}
}

void SiteswapGraph::PrimeFactorise_Divide(std::map<unsigned int, unsigned int> * p1, std::map<unsigned int, unsigned int> * p2)
{
	for (auto i = p2->begin(); i != p2->end(); i++)
	{
		(*p1)[i->first] -= i->second;
	}
}



unsigned int SiteswapGraph::Choose(const unsigned int & n, unsigned int k)
{
	// Choose values are reflective, choose the smallest value if necessary.

	if (k > ( n >> 1 ))
	{
		k = n - k;
	}

	// Deal with the easy option.

	if (k == 1)
	{
		return n;
	}

	// Otherwise head into prime factorisation.

	std::map<unsigned int, unsigned int> p_numerator, p_denominator;

	for (unsigned int i = 0; i < k - 1; i++)
	{
		std::map<unsigned int, unsigned int> * p_loop_numerator = PrimeFactorise(n - i),
			* p_loop_denominator = PrimeFactorise(k - i);

		PrimeFactorise_Multiply(&p_numerator, p_loop_numerator);
		PrimeFactorise_Multiply(&p_denominator, p_loop_denominator);

		delete p_loop_numerator;
		delete p_loop_denominator;
	}

	// Insert the final denominator multiplication.

	std::map<unsigned int, unsigned int> * p_final_numerator = PrimeFactorise(n - k + 1);
	PrimeFactorise_Multiply(&p_numerator, p_final_numerator);
	delete p_final_numerator;

	// Run the division.

	PrimeFactorise_Divide(&p_numerator, &p_denominator);

	// Compute the final result.

	unsigned int choose_return = 1;

	for (auto i = p_numerator.begin(); i != p_numerator.end(); i++)
	{
		for (unsigned int j = 0; j < i->second; j++)
		{
			choose_return *= i->first;
		}
	}

	return choose_return;
}

unsigned int SiteswapGraph::DeriveShortestPath(unsigned int state_start, const unsigned int& state_end)
{
	unsigned int actions_reserved = 0U, result = 0U;

	while ((state_start & ~state_end) || actions_reserved < Functions::Bits(~state_start & state_end))
	{
		if (state_start & 1U)
		{
			actions_reserved++;
		}

		state_start >>= 1U; result++;
	}

	return result;
}

bool SiteswapGraph::IsDestinationExtensionOfSource(const UIntStore& source, const UIntStore& destination)
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

void SiteswapGraph::AddPaths_Recursive(
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
			if (DoesPathExist(i->state_end, s_end, n - 1) && a.find(i->state_end) == a.end())
			{
				p_current.push_back(*i);
				a.insert(i->state_end);
				SiteswapGraph::AddPaths_Recursive(p, p_current, a, i->state_end, s_end, n - 1);
				p_current.pop_back();
				a.erase(i->state_end);
			}
		}
	}
}

void SiteswapGraph::AddPaths(
	std::deque<std::deque<SiteswapGraphConnection>>& p,
	std::set<SiteswapState>& a,
	const SiteswapState& s_begin,
	const SiteswapState& s_end,
	const unsigned int& n)
{
	if (a.find(s_begin) == a.end() &&
		a.find(s_end) == a.end() &&
		DoesPathExist(s_begin, s_end, n))
	{
		a.insert(s_begin);
		AddPaths_Recursive(p, std::deque<SiteswapGraphConnection>(), a, s_begin, s_end, n);
		a.erase(s_begin);
	}
}

SiteswapPattern * SiteswapGraph::GetRandomPattern(const unsigned int &b, const unsigned int &t, const unsigned int& max_throw)
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
			b,
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
		patterns->insert({ b, *i }); 
	}

	return patterns;
}

