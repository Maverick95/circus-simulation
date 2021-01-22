#ifndef GRAPH_DATA_PROCESSING_H
#define GRAPH_DATA_PROCESSING_H

#include "stdafx.h"

#include "SiteswapGraph.h"

namespace GraphDataProcessing
{
	void Initialize();
	void Shutdown();

	SiteswapGraph * GetSiteswapGraph();
}

#endif
