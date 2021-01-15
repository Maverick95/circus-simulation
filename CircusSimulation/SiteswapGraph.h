#ifndef SITESWAP_GRAPH_H
#define SITESWAP_GRAPH_H

class SiteswapGraph
{

private:

	static std::map<unsigned int, unsigned int> * PrimeFactorise(unsigned int);
	static void PrimeFactorise_Multiply(std::map<unsigned int, unsigned int> *, std::map<unsigned int, unsigned int> *);
	static void PrimeFactorise_Divide(std::map<unsigned int, unsigned int> *, std::map<unsigned int, unsigned int> *);
	static unsigned int Choose(const unsigned int &, unsigned int);

	unsigned int num_balls;
	unsigned int max_throw;
	unsigned int num_states;
	unsigned int max_state;

	unsigned int * states;

	std::forward_list<SiteswapGraphConnection> * connections;

	unsigned int ** shortest_paths;

	void ComputeMaxState();
	void ComputeStates();
	void ComputeConnections();
	void ComputeShortestPaths();
	void Initialize();
	
	unsigned int LookupState(const unsigned int &);
	unsigned int LookupState(const unsigned int &, const unsigned int &, const unsigned int &);

	void AddPaths_Recursive(std::deque<std::deque<SiteswapGraphConnection>> &,
		std::deque<SiteswapGraphConnection> &,
		bool *, const unsigned int, const unsigned int &, const unsigned int);

	void AddPaths(std::deque<std::deque<SiteswapGraphConnection>> &,
		bool *, const unsigned int &, const unsigned int &, const unsigned int &);

public:

	SiteswapGraph(const unsigned int &, const unsigned int &);
	SiteswapGraph(const SiteswapGraph &);
	
	~SiteswapGraph();

	SiteswapPattern * GetRandomPattern(const unsigned int &);
};

#endif
