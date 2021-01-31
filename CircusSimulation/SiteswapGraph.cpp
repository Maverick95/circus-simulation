#include <chrono>
#include <queue>
#include <random>

#include "Enum.h"
#include "Settings.h"
#include "SiteswapGraphShortestPathChain.h"

#include "SiteswapGraph.h"



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

unsigned int SiteswapGraph::Bits(unsigned int s)
{
	unsigned int result = 0U;

	while (s)
	{
		if (s & 1U)
		{
			result++;
		}

		s >>= 1U;
	}

	return result;
}

unsigned int SiteswapGraph::DeriveShortestPath(unsigned int state_start, const unsigned int& state_end)
{
	unsigned int actions_reserved = 0U, result = 0U;

	while ((state_start & ~state_end) || actions_reserved < Bits(~state_start & state_end))
	{
		if (state_start & 1U)
		{
			actions_reserved++;
		}

		state_start >>= 1U; result++;
	}

	return result;
}

void SiteswapGraph::ComputeConnections()
{
}

void SiteswapGraph::AddPaths_Recursive(std::deque<std::deque<SiteswapGraphConnection>> & p,
	std::deque<SiteswapGraphConnection> & p_current,
	bool * a, const unsigned int s_current, const unsigned int & s_end, const unsigned int n)
{
	if (n == 1)
	{
		for (auto i = connections[s_current].begin(); i != connections[s_current].end(); i++)
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
		for (auto i = connections[s_current].begin(); i != connections[s_current].end(); i++)
		{
			if (DeriveShortestPath(i->state_end, s_end) <= n - 1 && a[i->state_end])
			{
				p_current.push_back(*i);
				a[i->state_end] = false;
				SiteswapGraph::AddPaths_Recursive(p, p_current, a, i->state_end, s_end, n - 1);
				p_current.pop_back();
				a[i->state_end] = true;
			}
		}
	}
}

void SiteswapGraph::AddPaths(std::deque<std::deque<SiteswapGraphConnection>> & p,
	bool * a, const unsigned int & s_begin, const unsigned int & s_end, const unsigned int & n)
{
	if (a[s_begin] && a[s_end] && DeriveShortestPath(s_begin, s_end) <= n)
	{
		a[s_begin] = false;
		AddPaths_Recursive(p, std::deque<SiteswapGraphConnection>(), a, s_begin, s_end, n);
		a[s_begin] = true;
	}
}

SiteswapGraph::SiteswapGraph(const unsigned int & t)
	:
	max_throw(t < Settings::ThrowHeight_Maximum() ? t : Settings::ThrowHeight_Maximum()),
	num_states(1U << max_throw),
	max_state((1U << max_throw) - 1U),
	connections(new std::forward_list<SiteswapGraphConnection>[num_states]),
	balls_states()
{
	for (unsigned int i = 0U; i < num_states; i++)
	{
		balls_states[Bits(i)].push_back(i);

		// State may require a zero throw next.

		if ((i & 1U) == 0)
		{
			connections[i].push_front({ i, i >> 1U, 0 });
		}
		else
		{
			for (unsigned int j = 1U; j <= max_throw; j++)
			{
				if ((i & (1U << j)) == 0)
				{
					connections[i].push_front({ i, (i | (1U << j)) >> 1, j });
				}
			}
		}
	}
}

SiteswapGraph::SiteswapGraph(const SiteswapGraph & sg)
	:
	max_throw(sg.max_throw),
	num_states(sg.num_states),
	max_state(sg.max_state),
	connections(new std::forward_list<SiteswapGraphConnection>[num_states]),
	balls_states()
{
	for (unsigned int i = 0U; i < num_states; i++)
	{
		connections[i] = sg.connections[i];
	}

	balls_states = sg.balls_states;

}

SiteswapGraph::~SiteswapGraph()
{
	delete[] connections;
}

SiteswapPattern * SiteswapGraph::GetRandomPattern(const unsigned int & b, const unsigned int & t)
{
	if (b > max_throw) { return NULL; }

	bool* a = new bool[num_states];
	for (unsigned int i = 1U; i < num_states; i++) { a[i] = true; }
	std::deque<std::deque<SiteswapGraphConnection>> p;

	for (auto i = balls_states[b].begin(); i != balls_states[b].end(); i++)
	{
		unsigned int st = *i;

		if (a[st])
		{
			AddPaths(p, a, st, st, t);
			a[st] = false;

			for (unsigned int j = 1U; (st << j) <= max_state; j++)
			{
				a[st << j] = false;
			}
		}
	}

	delete[] a;

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

std::set<SiteswapPattern>* SiteswapGraph::GetPatterns(const unsigned int& b, const unsigned int& t)
{
	if (b > max_throw) { return NULL; }

	bool* a = new bool[num_states];
	for (unsigned int i = 1U; i < num_states; i++) { a[i] = true; }
	std::deque<std::deque<SiteswapGraphConnection>> p;

	for (auto i = balls_states[b].begin(); i != balls_states[b].end(); i++)
	{
		unsigned int st = *i;

		if (a[st])
		{
			AddPaths(p, a, st, st, t);
			a[st] = false;

			for (unsigned int j = 1U; (st << j) <= max_state; j++)
			{
				a[st << j] = false;
			}
		}
	}

	delete[] a;

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

unsigned int SiteswapGraph::GetMaxThrow() const
{
	return max_throw;
}

unsigned int SiteswapGraph::GetNumStates() const
{
	return num_states;
}

unsigned int SiteswapGraph::GetMaxState() const
{
	return max_state;
}