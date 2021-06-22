#ifndef BALL_STATUS_WINDOW
#define BALL_STATUS_WINDOW

#include "stdafx.h"

#include <wx\wx.h>

#include "RenderPatternWindow.h"

class BallStatusWindow : public ContextPatternWindow<wxAutoBufferedPaintDC>
{

private:

	wxStaticText ** pattern_balls;

protected:

	virtual void OnBallsUpdate();
	virtual void OnScreenUpdateD1(const long &);
	
	virtual void ResetD1();
	virtual void PopulateD1();
	virtual void StopD1();
	
	virtual void OnScreenPaintD1(wxAutoBufferedPaintDC* context);
	virtual void OnScreenResizeD1();


public:

	BallStatusWindow(wxWindow *);

	virtual ~BallStatusWindow();

};

#endif
