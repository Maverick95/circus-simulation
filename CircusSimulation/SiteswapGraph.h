#ifndef SITESWAP_GRAPH_H
#define SITESWAP_GRAPH_H

#include "stdafx.h"

#include <deque>
#include <forward_list>
#include <map>
#include <set>

#include "Struct.h"

namespace SiteswapGraph
{
	SiteswapPattern* GetRandomPattern(
		const unsigned int& numberBalls,
		const unsigned int& numberActions,
		const unsigned int& numberThrows,
		unsigned int maxThrow);

	std::set<SiteswapPattern>* GetPatterns(
		const unsigned int& numberBalls,
		const unsigned int& numberActions,
		const unsigned int& numberThrows,
		unsigned int maxThrow);
};

#endif
