#ifndef SINGLE_JUGGLER_WINDOW_H
#define SINGLE_JUGGLER_WINDOW_H

#include "stdafx.h"
#include "d2d1.h"

#include <wx\wx.h>

#include "DisplayJugglingWindow.h"

#include "SettingsEvents.h"



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

	void SetBallColour(SettingsEvents::SetColourEvent& event);

protected:

	virtual void OnScreenUpdate_DisplayPattern(const long& time_elapsed);

	virtual void OnScreenPaint_RenderPattern(ID2D1HwndRenderTarget* context);
	
	virtual void OnScreenResize_ContextPattern();

	virtual void Reset_DisplayJuggling();
	virtual void Populate_DisplayJuggling();
	virtual void SetNumberSites_DisplayJuggling();

public:

	SingleJugglerWindow(wxWindow * parent, const unsigned int * w_r_x = NULL, const unsigned int * w_r_y = NULL, const double & dr = 1.0);

	virtual ~SingleJugglerWindow();

	wxDECLARE_EVENT_TABLE();

};



#endif
