#ifndef DISPLAY_PATTERN_WINDOW_H
#define DISPLAY_PATTERN_WINDOW_H

#include "stdafx.h"

#include <wx\wx.h>
#include <wx\dcbuffer.h>

#include "DisplayPatternHandler.h"

class DisplayPatternWindow : public wxWindow
{

private:

	DisplayPatternHandler * handler;

	wxTimer * timer_update_screen;

	bool full_removal;

	void OnScreenUpdate(wxTimerEvent &);
	void OnScreenPaint(wxPaintEvent &);

	void OnBallsUpdate();

	void Reset();
	void Populate();

	// Control functions.

	void Play();
	void Stop();

	wxDECLARE_EVENT_TABLE();

protected:

	virtual DisplayPatternHandler * GetValidHandler();

	// Abstract functions - defines DisplayPatternWindow as abstract base class.

	virtual void OnScreenUpdate_Derived(const long &) = 0;
	virtual void OnScreenPaint_Derived(wxAutoBufferedPaintDC &) = 0;

	virtual void OnBallsUpdate_Derived() = 0;

	virtual void Reset_Derived() = 0;
	virtual void Populate_Derived() = 0;

	virtual void Stop_Derived() = 0;

public:

	DisplayPatternWindow(wxWindow *);

	virtual ~DisplayPatternWindow();

	friend class DisplayPatternHandler;
};

#endif
