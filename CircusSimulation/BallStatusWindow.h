#ifndef BALL_STATUS_WINDOW
#define BALL_STATUS_WINDOW

#include "stdafx.h"

#include <wx\wx.h>

#include "RenderPatternWindow.h"

class BallStatusWindow : public ContextPatternWindow<wxWindow>
{

private:

	wxStaticText ** pattern_balls;

protected:

	virtual void OnBallsUpdate();
	virtual void OnScreenUpdate(const long &);
	
	virtual void ResetD1();
	virtual void PopulateD1();
	virtual void StopD1();
	
	virtual void OnScreenPaint(wxWindow* context);
	virtual void OnScreenResize();


public:

	BallStatusWindow(wxWindow *);

	virtual ~BallStatusWindow();

};

#endif
