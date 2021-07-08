#ifndef POOL_JUGGLERS_2D_WINDOW
#define POOL_JUGGLERS_2D_WINDOW

#include "DisplayJugglingWindow.h"
#include <wx\wx.h>
#include "d2d1.h"

class PoolJugglers2dWindow : public DisplayJugglingWindow<ID2D1HwndRenderTarget>
{

private:

	double* site_x;
	double* site_y;

public:

	PoolJugglers2dWindow(wxWindow* parent, const unsigned int& ns);

	virtual ~PoolJugglers2dWindow();

};

#endif
