#ifndef DIRECT_2D_FACTORY_H
#define DIRECT_2D_FACTORY_H

#include "d2d1.h"

namespace Direct2dFactory
{
	void Setup();
	void Teardown();

	ID2D1Factory* GetDrawingFactory();
}

#endif
