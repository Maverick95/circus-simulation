#ifndef SINGLE_JUGGLER_WX_WINDOW_H
#define SINGLE_JUGGLER_WX_WINDOW_H

#include "stdafx.h"

#include <wx\wx.h>

#include "DisplayJugglingWindow.h"



class SingleJugglerWxWindow : public DisplayJugglingWindow<wxAutoBufferedPaintDC>
{

private:

	double dwell_ratio;

	double* plot_x;
	double* plot_y;

	double* window_ratios_x;
	double* window_ratios_y;

	unsigned int* window_widths_x;
	unsigned int* window_widths_y;

protected:

	virtual void OnScreenUpdateD1(const long&);
	virtual void OnScreenResizeD1();
	virtual void OnScreenPaintD1(wxAutoBufferedPaintDC* context);

	virtual void OnBallsUpdateD1();

	virtual void ResetD2();
	virtual void PopulateD2();

public:

	SingleJugglerWxWindow(wxWindow* parent, const unsigned int* w_r_x = NULL, const unsigned int* w_r_y = NULL, const double& dr = 1.0);

	virtual ~SingleJugglerWxWindow();

};



#endif
