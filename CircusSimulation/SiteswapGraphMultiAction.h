#ifndef SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H
#define SITESWAP_GRAPH_MULTI_ACTION_FUNCTIONS_H



#include "stdafx.h"

#include <forward_list>
#include <vector>

#include "Struct.h"
#include "UIntStore.h"

namespace SiteswapGraphMultiAction
{
	void StoreValidBeginStates(
		std::vector<UIntStore>& result,
		const unsigned int& numberActions,
		const unsigned int& maxThrow,
		const unsigned int& numberBits);

	void StoreNextStates(
		std::forward_list<SiteswapGraphConnection>& result,
		const UIntStore& current,
		const unsigned int& max);
}



#endif
