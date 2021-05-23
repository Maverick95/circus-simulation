#include "Direct2dFactory.h"

static ID2D1Factory* drawingFactory = NULL;

void Direct2dFactory::Setup()
{
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &drawingFactory);
}

void Direct2dFactory::Teardown()
{
	drawingFactory->Release();
	drawingFactory = NULL;
}

ID2D1Factory* Direct2dFactory::GetDrawingFactory()
{
	return drawingFactory;
}

