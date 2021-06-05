#ifndef STRUCT_H
#define STRUCT_H

#include "stdafx.h"

#include <deque>
#include <string>
#include <vector>

#include "UIntStore.h"

struct SiteswapGraphConnection
{
	SiteswapState state_begin;
	SiteswapState state_end;
	std::vector<UIntStoreTransferBit> state_transfer;
};

struct SiteswapPattern
{
	unsigned int num_balls;
	unsigned int num_actions;
	std::deque<SiteswapGraphConnection> throws;
};

namespace StructFunctions
{
	bool IsSiteswapPatternValid(const SiteswapPattern&);
	bool IsThrowValid(const SiteswapState&, const SiteswapState&, const SiteswapThrow&);
	
	std::string GetSiteswapPatternLookupLabel(const SiteswapPattern& pattern);
}

bool operator==(const SiteswapGraphConnection&, const SiteswapGraphConnection&);
bool operator!=(const SiteswapGraphConnection&, const SiteswapGraphConnection&);

bool operator<(const SiteswapPattern&, const SiteswapPattern&);
bool operator==(const SiteswapPattern&, const SiteswapPattern&);
bool operator!=(const SiteswapPattern&, const SiteswapPattern&);

std::ostream& operator<<(std::ostream&, const SiteswapPattern&);


#endif
