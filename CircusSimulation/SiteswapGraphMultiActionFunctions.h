#ifndef SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H
#define SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H



#include "stdafx.h"

#include <vector>

#include "UIntStore.h"

namespace SiteswapGraphMultiAction
{
	std::vector<UIntStore> BitSpread(const unsigned int& length, const unsigned int& max, const unsigned int& total);

	unsigned int BitLowest(const unsigned int& bits);

	bool BitNext(unsigned int& current, unsigned int max);

	std::vector<UIntStore> BitStates(const UIntStore& bitSpread, unsigned int max);

	std::vector<UIntStore> AllStates(const unsigned int& length, const unsigned int& max, const unsigned int& total);
}



#endif
