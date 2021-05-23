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

	virtual void OnBallsUpdate() = 0;
	virtual void OnScreenUpdateD1(const long &) = 0;
	virtual void ResetD1() = 0;
	virtual void PopulateD1() = 0;
	virtual void StopD1() = 0;

public:

	DisplayPatternWindow(wxWindow *);

	virtual ~DisplayPatternWindow();

	friend class DisplayPatternHandler;

	wxDECLARE_EVENT_TABLE();
};

#endif
