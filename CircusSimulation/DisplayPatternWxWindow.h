#ifndef DISPLAY_PATTERN_WX_WINDOW_H
#define DISPLAY_PATTERN_WX_WINDOW_H

#include <wx\wx.h>

#include "DisplayPatternWindow.h"

class DisplayPatternWxWindow : public DisplayPatternWindow
{

private:

	void OnScreenPaint(wxPaintEvent& e);

protected:

	virtual void OnScreenPaintD1(wxAutoBufferedPaintDC& dc) = 0;

public:

	DisplayPatternWxWindow(wxWindow* parent);
	virtual ~DisplayPatternWxWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
