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

	void OnScreenUpdate(wxTimerEvent&);

	void Reset();
	void Populate();

	// Control functions.

	void Play();
	void Stop();

protected:

	virtual DisplayPatternHandler* GetValidHandler();

	// Abstract functions - defines DisplayPatternWindow as abstract base class.

	virtual void OnBallsUpdate_DisplayPattern() = 0;
	virtual void OnScreenUpdate_DisplayPattern(const long &) = 0;
	virtual void Reset_DisplayPattern() = 0;
	virtual void Populate_DisplayPattern() = 0;
	virtual void Stop_DisplayPattern() = 0;

public:

	DisplayPatternWindow(wxWindow *);

	virtual ~DisplayPatternWindow();

	friend class DisplayPatternHandler;

	wxDECLARE_EVENT_TABLE();
};

#endif
