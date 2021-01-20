#ifndef BALL_STATUS_WINDOW
#define BALL_STATUS_WINDOW

#include "stdafx.h"

#include <wx\wx.h>

#include "DisplayPatternWindow.h"

class BallStatusWindow : public DisplayPatternWindow
{

private:

	wxStaticText ** pattern_balls;

protected:

	virtual void OnScreenUpdate_Derived(const long &);
	virtual void OnScreenPaint_Derived(wxAutoBufferedPaintDC &);

	virtual void Reset_Derived();
	virtual void Populate_Derived();

	virtual void Stop_Derived();

public:

	BallStatusWindow(wxWindow *);

	virtual ~BallStatusWindow();

	virtual void OnBallsUpdate_Derived();

};

#endif
