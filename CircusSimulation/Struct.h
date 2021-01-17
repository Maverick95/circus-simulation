#ifndef STRUCT_H
#define STRUCT_H

struct SiteswapGraphConnection
{
	unsigned int state_begin;
	unsigned int state_end;
	unsigned int state_begin_index;
	unsigned int state_end_index;
	unsigned int state_transfer_throw;
};

struct SiteswapPattern
{
	unsigned int num_balls;
	std::deque<SiteswapGraphConnection> throws;

	bool operator<(const SiteswapPattern&) const;
};

namespace StructFunctions
{
	bool IsSiteswapPatternValid(const SiteswapPattern &);
}

#endif
