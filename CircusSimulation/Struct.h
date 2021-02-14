#ifndef STRUCT_H
#define STRUCT_H

#include "stdafx.h"

#include <deque>

#include "UIntStore.h"

struct SiteswapGraphConnection
{
	SiteswapState state_begin;
	SiteswapState state_end;
	SiteswapThrow state_transfer_throw;
};

struct SiteswapPattern
{
	unsigned int num_balls;
	std::deque<SiteswapGraphConnection> throws;
};

namespace StructFunctions
{
	bool IsSiteswapPatternValid(const SiteswapPattern &);
	bool IsThrowValid(const SiteswapState&, const SiteswapState&, const SiteswapThrow&);
}

bool operator==(const SiteswapGraphConnection&, const SiteswapGraphConnection&);
bool operator!=(const SiteswapGraphConnection&, const SiteswapGraphConnection&);

bool operator<(const SiteswapPattern&, const SiteswapPattern&);
bool operator==(const SiteswapPattern&, const SiteswapPattern&);
bool operator!=(const SiteswapPattern&, const SiteswapPattern&);

std::ostream& operator<<(std::ostream&, const SiteswapPattern&);


#endif
