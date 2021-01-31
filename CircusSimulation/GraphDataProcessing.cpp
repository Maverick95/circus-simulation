#include <map>

#include "Settings.h"

#include "GraphDataProcessing.h"



static SiteswapGraph* DATA_GRAPHS;

void GraphDataProcessing::Initialize()
{
	unsigned int m = Settings::ThrowHeight_Maximum();
	DATA_GRAPHS = new SiteswapGraph(m);
}

void GraphDataProcessing::Shutdown()
{
	delete DATA_GRAPHS;
}

SiteswapGraph * GraphDataProcessing::GetSiteswapGraph()
{
	return DATA_GRAPHS;
}