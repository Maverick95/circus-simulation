#ifndef STDAFWX_H
#define STDAFWX_H

#include "stdafx.h"
#include "d2d1.h"

#include <wx\wx.h>

#include "DisplayJugglingWindow.h"

class SingleJugglerWindow : public DisplayJugglingWindow
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

	virtual void OnScreenUpdateD1(const long &);
	virtual void OnScreenResizeD1();
	virtual void OnScreenPaintD1(ID2D1HwndRenderTarget& context);

	virtual void OnBallsUpdateD1();

	virtual void ResetD2();
	virtual void PopulateD2();

public:

	SingleJugglerWindow(wxWindow * parent, const unsigned int * w_r_x = NULL, const unsigned int * w_r_y = NULL, const double & dr = 1.0);

	virtual ~SingleJugglerWindow();

};


#endif
