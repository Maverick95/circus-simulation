#ifndef GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H
#define GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H

#include <wx\wx.h>

class GetSingleJugglerPatternsWindow : public wxWindow
{

private:

	wxSpinCtrl* sp_throwHeightMax;

	void SetThrowHeightMaxBoundaries(wxSpinEvent& event);

public:

	GetSingleJugglerPatternsWindow(wxWindow* parent);
	virtual ~GetSingleJugglerPatternsWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
