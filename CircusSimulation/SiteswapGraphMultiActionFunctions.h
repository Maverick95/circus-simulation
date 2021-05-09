#ifndef SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H
#define SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H



#include "stdafx.h"

#include <forward_list>
#include <vector>

#include "Struct.h"
#include "UIntStore.h"

namespace SiteswapGraphMultiAction
{
	void StoreUniqueBitDistributions(
		std::vector<UIntStore>& result,
		const unsigned int& numberIntegers,
		const unsigned int& maxInteger,
		const unsigned int& sumIntegers);

	unsigned int GetLowestIntegerWithNBits(const unsigned int& n);

	void BitStates(
		std::vector<UIntStore>& result,
		const UIntStore& bitSpread,
		unsigned int max);

	void PopulateValidBeginStates(
		std::vector<UIntStore>& result,
		const unsigned int& length,
		const unsigned int& max,
		const unsigned int& total);

	void PopulateNextStates(
		std::forward_list<SiteswapGraphConnection>& result,
		const UIntStore& current,
		const unsigned int& max);
}



#endif
