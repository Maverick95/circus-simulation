#ifndef STRUCT_H
#define STRUCT_H

#include "stdafx.h"

#include <deque>
#include <ostream>

struct SiteswapGraphConnection
{
	unsigned int state_begin;
	unsigned int state_end;
	unsigned int state_transfer_throw;
};

struct SiteswapPattern
{
	unsigned int num_balls;
	std::deque<SiteswapGraphConnection> throws;
};

namespace StructFunctions
{
	bool IsSiteswapPatternValid(const SiteswapPattern &);
}

bool operator==(const SiteswapGraphConnection&, const SiteswapGraphConnection&);
bool operator!=(const SiteswapGraphConnection&, const SiteswapGraphConnection&);

bool operator<(const SiteswapPattern&, const SiteswapPattern&);
bool operator==(const SiteswapPattern&, const SiteswapPattern&);
bool operator!=(const SiteswapPattern&, const SiteswapPattern&);

std::ostream& operator<<(std::ostream&, const SiteswapPattern&);


#endif
