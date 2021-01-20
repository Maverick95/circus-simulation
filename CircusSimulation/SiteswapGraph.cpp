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

void SiteswapGraph::ComputeMaxState()
{
	unsigned int return_max_state = 0;

	for (unsigned int i = 0; i < num_balls; i++)
	{
		return_max_state += (1 << i);
	}

	max_state = return_max_state << (max_throw - num_balls);
}

void SiteswapGraph::ComputeStates()
{
	unsigned int ** store_combos = new unsigned int *[num_states];

	for (unsigned int i = 0; i < num_states; i++)
	{
		store_combos[i] = new unsigned int[num_balls];
		states[i] = 0;
	}

	// Set up data for algorithm.

	unsigned int * lp_combos = new unsigned int[num_balls];

	for (unsigned int i = 0; i < num_balls; i++)
	{
		lp_combos[i] = i + 1;
	}

	unsigned int store_index = 0;

	// Store initial combo.

	for (unsigned int i = 0; i < num_balls; i++)
	{
		store_combos[store_index][i] = lp_combos[i];
	}

	store_index++;

	// Main algorithm loop.

	unsigned int lp_index = 0;
	bool lp_continue = true;

	while (lp_continue)
	{
		if (lp_index == num_balls - 1)
		{
			if (lp_combos[lp_index] < max_throw)
			{
				lp_combos[lp_index]++;

				for (unsigned int i = 0; i < lp_index; i++)
				{
					lp_combos[i] = i + 1;
				}

				// Store combo.

				for (unsigned int i = 0; i < num_balls; i++)
				{
					store_combos[store_index][i] = lp_combos[i];
				}

				store_index++;

				lp_index = 0;
			}
			else
			{
				lp_continue = false;
			}
		}
		else
		{
			if (lp_combos[lp_index] < lp_combos[lp_index + 1] - 1)
			{
				lp_combos[lp_index]++;

				for (unsigned int i = 0; i < lp_index; i++)
				{
					lp_combos[i] = i + 1;
				}

				// Store combo.

				for (unsigned int i = 0; i < num_balls; i++)
				{
					store_combos[store_index][i] = lp_combos[i];
				}

				store_index++;

				lp_index = 0;
			}
			else
			{
				lp_index++;
			}
		}
	}

	// Use the results to compute the final states.

	for (unsigned int i = 0; i < num_states; i++)
	{
		for (unsigned int j = 0; j < num_balls; j++)
		{
			states[i] += 1u << (store_combos[i][j] - 1);
		}
	}

	// Deallocate all the memory.

	for (unsigned int i = 0; i < num_states; i++)
	{
		delete[] store_combos[i];
	}

	delete[] store_combos;
	delete[] lp_combos;
}

unsigned int SiteswapGraph::LookupState(const unsigned int & s)
{
	return LookupState(s, 0, num_states);
}

unsigned int SiteswapGraph::LookupState(const unsigned int & s, const unsigned int & a, const unsigned int & b)
{
	unsigned int m = a + ((b - a - (((b - a) & 1u) == 0 ? 0 : 1)) / 2);

	if (states[m] == s)
	{
		return m;
	}
	else if (states[m] > s)
	{
		return LookupState(s, a, m);
	}
	else
	{
		return LookupState(s, m + 1, b);
	}
}

void SiteswapGraph::ComputeConnections()
{
	for (unsigned int i = 0; i < num_states; i++)
	{
		// State may require a zero throw next.

		if ((states[i] & 1u) == 0)
		{
			connections[i].push_front(
			{
				states[i],
				states[i] >> 1,
				i,
				LookupState(states[i] >> 1),
				0
			});
		}
		else
		{
			for (unsigned int j = 1; j <= max_throw; j++)
			{
				if ((states[i] & (1u << j)) == 0)
				{
					connections[i].push_front(
					{
						states[i],
						(states[i] | (1u << j)) >> 1,
						i,
						LookupState((states[i] | (1u << j)) >> 1),
						j
					});
				}
			}
		}
	}
}

void SiteswapGraph::ComputeShortestPaths()
{
	// Initialize shortest paths.

	for (unsigned int i = 0; i < num_states; i++)
	{
		shortest_paths[i] = new unsigned int[num_states];
		for (unsigned int j = 0; j < num_states; j++)
		{
			shortest_paths[i][j] = 0;
		}
	}

	// Run the algorithm.

	// Set up state data structures.

	bool * state_properties_end = new bool[num_states];
	unsigned int * state_properties_sink = new unsigned int[num_states];

	for (unsigned int i = 0; i < num_states; i++)
	{
		state_properties_end[i] = false;
		state_properties_sink[i] = num_states;
	}

	// Set up the obvious shortest paths.

	for (unsigned int i = 0; (states[i] << 1) <= max_state; i++)
	{
		for (unsigned int j = 1; (states[i] << j) <= max_state; j++)
		{
			shortest_paths[LookupState(states[i] << j)][i] = j;
			state_properties_sink[i]--;
		}
	}

	// Set up initial chain.

	std::queue<SiteswapGraphShortestPathChain> * chains = new std::queue<SiteswapGraphShortestPathChain>;
	std::queue<SiteswapGraphShortestPathChain> * chains_new = NULL;

	chains->push(SiteswapGraphShortestPathChain(0, 1));
	state_properties_end[0] = true;

	// Begin main loop.

	while (!chains->empty())
	{
		chains_new = new std::queue<SiteswapGraphShortestPathChain>;

		while (!chains->empty())
		{
			SiteswapGraphShortestPathChain & c_old = chains->front();

			// Create new chains based on connections.

			for (auto it = connections[c_old.End()->StateIndex()].begin();
				it != connections[c_old.End()->StateIndex()].end(); it++)
			{
				// Case depending on sink status.

				if (state_properties_sink[it->state_end_index] > 0)
				{
					SiteswapGraphShortestPathChain c_old_extension(c_old);
					c_old_extension.PushBack(it->state_end_index, 1);

					// Now loop through the new chain from begin to end.

					while (c_old_extension.Current() != c_old_extension.End())
					{
						// If shortest path not yet found, populate.

						if (shortest_paths[c_old_extension.Current()->StateIndex()][c_old_extension.End()->StateIndex()] == 0)
						{
							shortest_paths[c_old_extension.Current()->StateIndex()][c_old_extension.End()->StateIndex()] = c_old_extension.ChainLengthCurrent();
							state_properties_sink[c_old_extension.End()->StateIndex()]--;

							// If values are not equal, fill in the other shortest paths by multiplying up from the current node.

							if (c_old_extension.Current()->StateIndex() != c_old_extension.End()->StateIndex())
							{
								for (unsigned int i = 1; (states[c_old_extension.Current()->StateIndex()] << i) <= max_state; i++)
								{
									unsigned int
										x = LookupState(states[c_old_extension.Current()->StateIndex()] << i),
										y = c_old_extension.End()->StateIndex();

									if (shortest_paths[x][y] == 0)
									{
										shortest_paths[x][y] = c_old_extension.ChainLengthCurrent() + i;
										state_properties_sink[y]--;
									}
								}
							}

							// If values are equal, chop off.

							if (c_old_extension.Current()->StateIndex() == c_old_extension.End()->StateIndex())
							{
								c_old_extension.RemoveCurrentNode();
							}

							else
							{
								c_old_extension.GetNext();
							}
						}

						// Otherwise delete.

						else
						{
							c_old_extension.RemoveCurrentNode();
						}
					}

					c_old_extension.Reset();

					// Only push chain if ends with an odd state.

					if ((states[c_old_extension.End()->StateIndex()] & 1) != 0)
					{
						if (c_old_extension.ChainCount() > 1)
						{
							if (!state_properties_end[c_old_extension.End()->StateIndex()])
							{
								state_properties_end[c_old_extension.End()->StateIndex()] = true;
							}

							chains_new->push(c_old_extension);
						}
						else if (!state_properties_end[c_old_extension.End()->StateIndex()])
						{
							chains_new->push(c_old_extension);
							state_properties_end[c_old_extension.End()->StateIndex()] = true;
						}
					}
				}
			}

			chains->pop();
		}

		// Move new chains into chains to be examined (next iteration).

		delete chains;
		chains = chains_new;
		chains_new = NULL;
	}

	delete chains;
	delete[] state_properties_end;
	delete[] state_properties_sink;
}

void SiteswapGraph::Initialize()
{
	ComputeMaxState();
	ComputeStates();
	ComputeConnections();
	//ComputeShortestPaths();
}

void SiteswapGraph::AddPaths_Recursive(std::deque<std::deque<SiteswapGraphConnection>> & p,
	std::deque<SiteswapGraphConnection> & p_current,
	bool * a, const unsigned int s_current, const unsigned int & s_end, const unsigned int n)
{
	if (n == 1)
	{
		for (auto i = connections[s_current].begin(); i != connections[s_current].end(); i++)
		{
			if (i->state_end_index == s_end)
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
			if (GetShortestPath(i->state_end_index, s_end) <= n - 1 && a[i->state_end_index])
			{
				p_current.push_back(*i);
				a[i->state_end_index] = false;
				SiteswapGraph::AddPaths_Recursive(p, p_current, a, i->state_end_index, s_end, n - 1);
				p_current.pop_back();
				a[i->state_end_index] = true;
			}
		}
	}
}

void SiteswapGraph::AddPaths(std::deque<std::deque<SiteswapGraphConnection>> & p,
	bool * a, const unsigned int & s_begin, const unsigned int & s_end, const unsigned int & n)
{
	if (a[s_begin] && a[s_end] && GetShortestPath(s_begin, s_end) <= n)
	{
		a[s_begin] = false;
		AddPaths_Recursive(p, std::deque<SiteswapGraphConnection>(), a, s_begin, s_end, n);
		a[s_begin] = true;
	}
}

unsigned int SiteswapGraph::GetShortestPath(const unsigned int& s_begin, const unsigned int& s_end) const
{
	switch (Settings::SiteswapGraph_ShortestPathMethod())
	{
	case SiteswapGraphShortestPathMethod::METHOD_LOOKUP:
		return shortest_paths[s_begin][s_end];
	case SiteswapGraphShortestPathMethod::METHOD_DERIVED:
		return DeriveShortestPath(states[s_begin], states[s_end]);
	}
}

SiteswapGraph::SiteswapGraph(const unsigned int & b, const unsigned int & t)
	:
	num_balls(b == 0 ? 1 : b),
	max_throw(t < num_balls ? num_balls : t),
	num_states(Choose(max_throw, num_balls)),
	states(new unsigned int[num_states]),
	connections(new std::forward_list<SiteswapGraphConnection>[num_states]),
	shortest_paths(NULL)// new unsigned int * [num_states])
{
	Initialize();
}

SiteswapGraph::SiteswapGraph(const SiteswapGraph & sg)
	:
	num_balls(sg.num_balls),
	max_throw(sg.max_throw),
	num_states(sg.num_states),
	max_state(sg.max_state),
	states(new unsigned int[num_states]),
	connections(new std::forward_list<SiteswapGraphConnection>[num_states]),
	shortest_paths(NULL)//new unsigned int * [num_states])
{
	for (unsigned int i = 0; i < num_states; i++)
	{
		states[i] = sg.states[i];
		connections[i] = sg.connections[i];
		
		/*
		shortest_paths[i] = new unsigned int[num_states];

		for (unsigned int j = 0; j < num_states; j++)
		{
			shortest_paths[i][j] = sg.shortest_paths[i][j];
		}
		*/
	}
}

SiteswapGraph::~SiteswapGraph()
{
	delete[] states;
	delete[] connections;

	/*
	for (unsigned int i = 0; i < num_states; i++)
	{
		delete[] shortest_paths[i];
	}

	delete[] shortest_paths;
	*/
}

SiteswapPattern * SiteswapGraph::GetRandomPattern(const unsigned int & n)
{
	bool * a = new bool[num_states];
	for (unsigned int i = 0; i < num_states; i++) { a[i] = true; }
	std::deque<std::deque<SiteswapGraphConnection>> p;

	for (unsigned int i = 0; i < num_states; i++)
	{
		if (a[i])
		{
			AddPaths(p, a, i, i, n);
			a[i] = false;

			for (unsigned int j = 1; (states[i] << j) <= max_state; j++)
			{
				unsigned int x = LookupState(states[i] << j);
				a[x] = false;
			}
		}
	}

	delete[] a;

	if (p.size() == 0)
	{
		return NULL;
	}

	return new SiteswapPattern
	{
		num_balls,
		*(
			p.begin() +
			std::uniform_int_distribution<unsigned int>(0, p.size() - 1)(
				std::default_random_engine(
					std::chrono::system_clock::now().time_since_epoch().count() ))
			)
	};
}

std::set<SiteswapPattern>* SiteswapGraph::GetPatterns(const unsigned int& n)
{
	bool* a = new bool[num_states];
	for (unsigned int i = 0; i < num_states; i++) { a[i] = true; }
	std::deque<std::deque<SiteswapGraphConnection>> p;

	for (unsigned int i = 0; i < num_states; i++)
	{
		if (a[i])
		{
			AddPaths(p, a, i, i, n);
			a[i] = false;

			for (unsigned int j = 1; (states[i] << j) <= max_state; j++)
			{
				unsigned int x = LookupState(states[i] << j);
				a[x] = false;
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
		patterns->insert({ num_balls, *i });
	}

	return patterns;
}



