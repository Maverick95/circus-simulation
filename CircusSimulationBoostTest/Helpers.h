#ifndef HELPERS_H
#define HELPERS_H

#include "Struct.h"

SiteswapGraphConnection GenerateSingleActionConnection(
	const unsigned int& state_source,
	const unsigned int& state_destination,
	const unsigned int& state_transfer_throw);

#endif
