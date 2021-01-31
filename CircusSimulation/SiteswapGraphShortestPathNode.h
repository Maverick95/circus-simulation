#ifndef SSG_SHORTEST_PATH_NODE_H
#define SSG_SHORTEST_PATH_NODE_H

#include "stdafx.h"

class SiteswapGraphShortestPathNode
{

private:

	unsigned int state_index;
	unsigned int node_length;

	SiteswapGraphShortestPathNode * node_chain_previous = NULL;
	SiteswapGraphShortestPathNode * node_chain_next = NULL;

public:

	SiteswapGraphShortestPathNode(const unsigned int &);
	SiteswapGraphShortestPathNode(const unsigned int &, const unsigned int &);

	~SiteswapGraphShortestPathNode();

	unsigned int StateIndex() const;
	unsigned int NodeLength() const;

	friend class SiteswapGraphShortestPathChain;

};

#endif
