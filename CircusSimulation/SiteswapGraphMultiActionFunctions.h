#ifndef SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H
#define SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H



#include "stdafx.h"

#include <forward_list>
#include <vector>

#include "Struct.h"
#include "UIntStore.h"

namespace SiteswapGraphMultiAction
{
	void BitSpread(
		std::vector<UIntStore>& result,
		const unsigned int& length,
		const unsigned int& max,
		const unsigned int& total);

	unsigned int BitLowest(const unsigned int& bits);

	void BitStates(
		std::vector<UIntStore>& result,
		const UIntStore& bitSpread,
		unsigned int max);

	void AllStates(
		std::vector<UIntStore>& result,
		const unsigned int& length,
		const unsigned int& max,
		const unsigned int& total);

	void NextStates(
		std::forward_list<SiteswapGraphConnection>& result,
		const UIntStore& current,
		const unsigned int& max);
}



#endif
