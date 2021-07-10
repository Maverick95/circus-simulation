#ifndef POOL_JUGGLERS_2D_WINDOW
#define POOL_JUGGLERS_2D_WINDOW

#include "DisplayJugglingWindow.h"
#include <wx\wx.h>
#include "d2d1.h"

class PoolJugglers2dWindow final : public DisplayJugglingWindow<ID2D1HwndRenderTarget>
{

private:

	double* site_x;
	double* site_y;

	double* plot_x;
	double* plot_y;

	ID2D1SolidColorBrush* brushBlack;

	void UpdateSiteCoordinates();

protected:

	virtual void OnScreenUpdate_DisplayPattern(const long& time_elapsed);

	virtual void OnScreenPaint_RenderPattern(ID2D1HwndRenderTarget* context);

	virtual void OnScreenResize_ContextPattern();

	virtual void OnBallsUpdate_DisplayJuggling();
	virtual void Reset_DisplayJuggling();
	virtual void Populate_DisplayJuggling();

public:

	PoolJugglers2dWindow(wxWindow* parent, const unsigned int& ns);

	virtual ~PoolJugglers2dWindow();

};

#endif
