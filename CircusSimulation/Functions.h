#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "stdafx.h"
#include <vector>

namespace Functions
{
	unsigned int Choose(const unsigned int&, unsigned int);
	unsigned int LowestCommonMultiple(const std::vector<unsigned int>&);
	unsigned int LowestCommonMultiple(unsigned int *, const unsigned int &);
	unsigned int Bits(unsigned int);
}

#endif
