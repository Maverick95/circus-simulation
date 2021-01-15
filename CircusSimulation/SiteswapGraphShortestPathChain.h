#ifndef SSG_SHORTEST_PATH_CHAIN_H
#define SSG_SHORTEST_PATH_CHAIN_H

class SiteswapGraphShortestPathChain
{

private:

	unsigned int chain_length;
	unsigned int chain_count;
	unsigned int chain_length_current;

	bool empty;

	SiteswapGraphShortestPathNode * node_begin;
	SiteswapGraphShortestPathNode * node_current;
	SiteswapGraphShortestPathNode * node_end;

public:

	SiteswapGraphShortestPathChain();
	SiteswapGraphShortestPathChain(const unsigned int &, const unsigned int &);
	SiteswapGraphShortestPathChain(const SiteswapGraphShortestPathChain &);

	~SiteswapGraphShortestPathChain();

	void PushBack(const unsigned int &, const unsigned int &);

	bool GetNext();
	void Reset();

	const SiteswapGraphShortestPathNode* Begin() const;
	const SiteswapGraphShortestPathNode* Current() const;
	const SiteswapGraphShortestPathNode* End() const;

	unsigned int ChainLength() const;
	unsigned int ChainCount() const;
	unsigned int ChainLengthCurrent() const;

	void RemoveCurrentNode();

};

#endif
