#ifndef SINGLE_JUGGLER_WINDOW_H
#define SINGLE_JUGGLER_WINDOW_H

#include "stdafx.h"
#include "d2d1.h"

#include <wx\wx.h>

#include "DisplayJugglingWindow.h"



class SingleJugglerWindow final : public DisplayJugglingWindow<ID2D1HwndRenderTarget>
{

private:

	double dwell_ratio;

	double * plot_x;
	double * plot_y;

	double * window_ratios_x;
	double * window_ratios_y;

	unsigned int * window_widths_x;
	unsigned int * window_widths_y;

	ID2D1SolidColorBrush* brushCircles;
	ID2D1SolidColorBrush* brushCirclesOutlines;

protected:

	virtual void OnScreenUpdate_DisplayPattern(const long &);

	virtual void OnScreenPaint_RenderPattern(ID2D1HwndRenderTarget* context);
	
	virtual void OnScreenResize_ContextPattern();

	virtual void OnBallsUpdate_DisplayJuggling();
	virtual void Reset_DisplayJuggling();
	virtual void Populate_DisplayJuggling();

public:

	SingleJugglerWindow(wxWindow * parent, const unsigned int * w_r_x = NULL, const unsigned int * w_r_y = NULL, const double & dr = 1.0);

	virtual ~SingleJugglerWindow();

};



#endif
