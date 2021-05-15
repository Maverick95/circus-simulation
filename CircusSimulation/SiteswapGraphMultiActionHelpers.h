#ifndef SITESWAP_GRAPH_MULTI_ACTION_HELPERS
#define SITESWAP_GRAPH_MULTI_ACTION_HELPERS

#include <vector>

#include "UIntStore.h"

namespace SiteswapGraphMultiActionHelpers
{
	void StoreValidSpreadsOfBitsAcrossActions(
		std::vector<UIntStore>& result,
		const unsigned int& numberActions,
		const unsigned int& maxThrow,
		const unsigned int& numberBits);

	void BitStates(
		std::vector<UIntStore>& result,
		const UIntStore& bitSpread,
		unsigned int max);
}

#endif




