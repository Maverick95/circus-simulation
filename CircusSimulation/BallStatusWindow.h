#ifndef BALL_STATUS_WINDOW
#define BALL_STATUS_WINDOW

#include "stdafx.h"

#include <wx\wx.h>

#include "RenderPatternWindow.h"

class BallStatusWindow final : public ContextPatternWindow<wxWindow>
{

private:

	wxStaticText ** pattern_balls;

protected:

	virtual void OnBallsUpdate_DisplayPattern();
	virtual void OnScreenUpdate_DisplayPattern(const long &);
	virtual void Reset_DisplayPattern();
	virtual void Populate_DisplayPattern();
	virtual void Stop_DisplayPattern();
	
	virtual void OnScreenPaint_RenderPattern(wxWindow* context);
	virtual void OnScreenResize_RenderPattern();


public:

	BallStatusWindow(wxWindow *);

	virtual ~BallStatusWindow();

};

#endif
