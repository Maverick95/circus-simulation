#ifndef SITESWAP_GRAPH_H
#define SITESWAP_GRAPH_H

#include "stdafx.h"

#include <deque>
#include <forward_list>
#include <map>
#include <set>

#include "Struct.h"

class SiteswapGraph
{

private:

	static void AddPaths_Recursive(
		std::deque<std::deque<SiteswapGraphConnection>>&,
		std::deque<SiteswapGraphConnection>&,
		std::set<SiteswapState>&,
		const SiteswapState&,
		const SiteswapState&,
		const unsigned int);

	static void AddPaths(
		std::deque<std::deque<SiteswapGraphConnection>>&,
		std::set<SiteswapState>&,
		const SiteswapState&,
		const SiteswapState&,
		const unsigned int&);

public:

	static std::map<unsigned int, unsigned int>* PrimeFactorise(unsigned int);
	static void PrimeFactorise_Multiply(std::map<unsigned int, unsigned int>*, std::map<unsigned int, unsigned int>*);
	static void PrimeFactorise_Divide(std::map<unsigned int, unsigned int>*, std::map<unsigned int, unsigned int>*);
	static unsigned int Choose(const unsigned int&, unsigned int);

	static unsigned int DeriveShortestPath(unsigned int, const unsigned int&);

	static bool IsDestinationExtensionOfSource(const UIntStore&, const UIntStore&);
	static bool DoesPathExist(const UIntStore&, const UIntStore&, const unsigned int&);

	static SiteswapPattern * GetRandomPattern(const unsigned int&, const unsigned int&, const unsigned int&);
	static std::set<SiteswapPattern>* GetPatterns(const unsigned int&, const unsigned int&, const unsigned int&);

};

#endif
