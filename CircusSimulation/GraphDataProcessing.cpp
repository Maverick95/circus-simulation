#include <map>

#include "Settings.h"

#include "GraphDataProcessing.h"



static std::map<unsigned int, SiteswapGraph *> DATA_GRAPHS;

void GraphDataProcessing::Initialize()
{
	unsigned int m = Settings::ThrowHeight_Maximum();

	for (unsigned int i = Settings::NumberBalls_Minimum(); i <= Settings::NumberBalls_Maximum(); i++)
	{
		DATA_GRAPHS.insert(std::pair<unsigned int, SiteswapGraph *>(i, new SiteswapGraph(i, m)));
	}
}

void GraphDataProcessing::Shutdown()
{
	for (auto i = DATA_GRAPHS.begin(); i != DATA_GRAPHS.end(); i++)
	{
		delete i->second;
	}
}

SiteswapGraph * GraphDataProcessing::GetSiteswapGraph(const unsigned int & num_balls)
{
	if (DATA_GRAPHS.find(num_balls) == DATA_GRAPHS.end())
	{
		return NULL;
	}

	return DATA_GRAPHS[num_balls];
}