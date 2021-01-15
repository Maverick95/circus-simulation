#include "stdafx.h"

SiteswapGraphShortestPathChain::SiteswapGraphShortestPathChain()
	:
	chain_length(0),
	chain_count(0),
	chain_length_current(0),
	empty(true),
	node_begin(NULL),
	node_end(NULL),
	node_current(NULL)
{

}

SiteswapGraphShortestPathChain::SiteswapGraphShortestPathChain(const unsigned int & si, const unsigned int & nl)
	:
	chain_length(0),
	chain_count(0),
	chain_length_current(0),
	empty(true)
{
	PushBack(si, nl);
}

SiteswapGraphShortestPathChain::SiteswapGraphShortestPathChain(const SiteswapGraphShortestPathChain & spc)
	:
	chain_length(spc.chain_length),
	chain_count(spc.chain_count),
	chain_length_current(spc.chain_length_current),
	empty(spc.empty),
	node_begin(NULL),
	node_end(NULL),
	node_current(NULL)
{
	if (!spc.empty)
	{
		SiteswapGraphShortestPathNode * n_original_current = spc.node_begin, * n_original_next = NULL;

		node_begin = new SiteswapGraphShortestPathNode(n_original_current->state_index, n_original_current->node_length);

		SiteswapGraphShortestPathNode * n_new_current = node_begin, * n_new_next = NULL;

		if (n_original_current == spc.node_current)
		{
			node_current = n_new_current;
		}

		while (n_original_current->node_chain_next != NULL)
		{
			n_original_next = n_original_current->node_chain_next;

			n_new_next = new SiteswapGraphShortestPathNode(n_original_next->state_index, n_original_next->node_length);

			n_new_current->node_chain_next = n_new_next;
			n_new_next->node_chain_previous = n_new_current;

			n_original_current = n_original_next;
			n_new_current = n_new_next;

			if (n_original_current == spc.node_current)
			{
				node_current = n_new_current;
			}
		}

		node_end = n_new_current;
	}
}

SiteswapGraphShortestPathChain::~SiteswapGraphShortestPathChain()
{
	if (!empty)
	{
		SiteswapGraphShortestPathNode * n = node_begin;

		while (n->node_chain_next != NULL)
		{
			n = n->node_chain_next;
			delete n->node_chain_previous;
		}

		delete n;
	}
}

void SiteswapGraphShortestPathChain::PushBack(const unsigned int & si, const unsigned int & nl)
{
	SiteswapGraphShortestPathNode * n = new SiteswapGraphShortestPathNode(si, nl);

	if (empty)
	{
		node_begin = n;
		node_end = n;
		node_current = n;
		empty = false;
	}
	else
	{
		node_end->node_chain_next = n;
		n->node_chain_previous = node_end;
		node_end = n;

		chain_length_current += nl;
		chain_length += nl;
	}

	chain_count++;
}

bool SiteswapGraphShortestPathChain::GetNext()
{
	bool return_value = false;

	if (!empty)
	{
		if (node_current->node_chain_next != NULL)
		{
			chain_length_current -= node_current->node_length;
			node_current = node_current->node_chain_next;
			return_value = true;
		}
	}

	return return_value;
}

void SiteswapGraphShortestPathChain::Reset()
{
	if (!empty)
	{
		node_current = node_begin;

		if (chain_count > 1)
		{
			chain_length_current = chain_length;
		}
	}
}

const SiteswapGraphShortestPathNode* SiteswapGraphShortestPathChain::Begin() const
{
	return node_begin;
}

const SiteswapGraphShortestPathNode* SiteswapGraphShortestPathChain::Current() const
{
	return node_current;
}

const SiteswapGraphShortestPathNode* SiteswapGraphShortestPathChain::End() const
{
	return node_end;
}

unsigned int SiteswapGraphShortestPathChain::ChainLength() const
{
	return chain_length;
}

unsigned int SiteswapGraphShortestPathChain::ChainCount() const
{
	return chain_count;
}

unsigned int SiteswapGraphShortestPathChain::ChainLengthCurrent() const
{
	return chain_length_current;
}

void SiteswapGraphShortestPathChain::RemoveCurrentNode()
{
	if (!empty)
	{
		if (chain_count == 1)
		{
			delete node_current;
			
			node_begin = NULL;
			node_current = NULL;
			node_end = NULL;
			
			chain_count--;
			empty = true;
		}
		else if (node_current == node_begin)
		{
			SiteswapGraphShortestPathNode * n = node_current;
			
			chain_length -= n->node_length;
			chain_length_current -= n->node_length;

			node_begin = n->node_chain_next;
			node_current = node_begin;

			delete n;
			node_current->node_chain_previous = NULL;

			chain_count--;
		}
		else if (node_current == node_end)
		{
			SiteswapGraphShortestPathNode * n = node_current;

			n->node_chain_previous->node_length += n->node_length;
			
			node_current = n->node_chain_previous;
			node_end = node_current;

			delete n;
			node_current->node_chain_next = NULL;

			chain_count--;
		}
		else
		{
			SiteswapGraphShortestPathNode * n = node_current;

			n->node_chain_previous->node_length += n->node_length;

			n->node_chain_previous->node_chain_next = n->node_chain_next;
			n->node_chain_next->node_chain_previous = n->node_chain_previous;
			node_current = n->node_chain_next;

			chain_length_current -= n->node_length;

			delete n;

			chain_count--;
		}
	}
}
