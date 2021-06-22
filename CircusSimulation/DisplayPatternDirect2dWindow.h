#ifndef DISPLAY_PATTERN_DIRECT_2D_WINDOW
#define DISPLAY_PATTERN_DIRECT_2D_WINDOW

#include <wx\wx.h>
#include "d2d1.h"

#include "DisplayPatternWindow.h"

class DisplayPatternDirect2dWindow : public DisplayPatternWindow
{

private:

	ID2D1HwndRenderTarget* renderTarget;

	void OnScreenResize(wxSizeEvent& e);
	void OnScreenPaint(wxPaintEvent& e);

protected:

	ID2D1HwndRenderTarget& GetRenderTarget();

	virtual void OnScreenResizeD1() = 0;
	virtual void OnScreenPaintD1(ID2D1HwndRenderTarget& context) = 0;

public:

	DisplayPatternDirect2dWindow(wxWindow*);
	virtual ~DisplayPatternDirect2dWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
