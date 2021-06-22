#ifndef BALL_STATUS_WINDOW
#define BALL_STATUS_WINDOW

#include "stdafx.h"

#include <wx\wx.h>

#include "DisplayPatternWxWindow.h"

class BallStatusWindow : public DisplayPatternWxWindow
{

private:

	wxStaticText ** pattern_balls;

protected:

	virtual void OnBallsUpdate();
	virtual void OnScreenUpdateD1(const long &);
	
	virtual void ResetD1();
	virtual void PopulateD1();
	virtual void StopD1();
	
	virtual void OnScreenPaintD1(wxAutoBufferedPaintDC& context);


public:

	BallStatusWindow(wxWindow *);

	virtual ~BallStatusWindow();

};

#endif
