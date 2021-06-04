#ifndef GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H
#define GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H

#include "Enum.h"

#include <wx\wx.h>

class GetSingleJugglerPatternsWindow : public wxWindow
{

private:

	wxSpinCtrl* sp_numberBalls;
	wxSpinCtrl* sp_numberThrows;
	wxSpinCtrl* sp_throwHeightMax;

	wxRadioButton* rd_patternTypeAsync;
	wxRadioButton* rd_patternTypeSync;

	wxRadioButton* rd_startingStateStandard;
	wxRadioButton* rd_startingStateExcited;
	wxRadioButton* rd_startingStateBoth;

	PatternQuerySingleJugglerType type;
	PatternQueryStartingState startingState;

	void SetRadioButtonStatuses();

	void SetThrowHeightMaxBoundaries(wxSpinEvent& event);

	void SetTypeAsync(wxCommandEvent& event);
	void SetTypeSync(wxCommandEvent& event);

	void SetStartingStateStandard(wxCommandEvent& event);
	void SetStartingStateExcited(wxCommandEvent& event);
	void SetStartingStateBoth(wxCommandEvent& event);

public:

	GetSingleJugglerPatternsWindow(wxWindow* parent);
	virtual ~GetSingleJugglerPatternsWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
