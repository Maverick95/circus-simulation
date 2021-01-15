#ifndef GRAPH_DATA_PROCESSING_H
#define GRAPH_DATA_PROCESSING_H

namespace GraphDataProcessing
{
	void Initialize();
	void Shutdown();

	SiteswapGraph * GetSiteswapGraph(const unsigned int &);
}

#endif
