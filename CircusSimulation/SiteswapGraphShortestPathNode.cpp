#include "SiteswapGraphShortestPathNode.h"



SiteswapGraphShortestPathNode::SiteswapGraphShortestPathNode(const unsigned int & si)
	:
	state_index(si),
	node_length(1)
{

}

SiteswapGraphShortestPathNode::SiteswapGraphShortestPathNode(const unsigned int & si, const unsigned int & nl)
	:
	state_index(si),
	node_length(nl)
{

}

SiteswapGraphShortestPathNode::~SiteswapGraphShortestPathNode()
{

}

unsigned int SiteswapGraphShortestPathNode::StateIndex() const
{
	return state_index;
}

unsigned int SiteswapGraphShortestPathNode::NodeLength() const
{
	return node_length;
}