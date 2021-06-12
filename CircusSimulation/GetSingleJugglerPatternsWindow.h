#ifndef GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H
#define GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H

#include "Enum.h"

#include <wx\wx.h>
#include <wx\listctrl.h>

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

	wxListCtrl* ls_patterns;

	wxButton* bt_find;

	PatternQuerySingleJugglerType singleJugglerType;
	PatternQueryStartingState startingState;

	void SetRadioButtonStatuses();

	void SetThrowHeightMaxBoundaries(
		const unsigned int& numberBalls,
		const unsigned int& throwHeightMax,
		const PatternQuerySingleJugglerType& type);

	void SetNumberBalls(wxSpinEvent& event);

	void SetTypeAsync(wxCommandEvent& event);
	void SetTypeSync(wxCommandEvent& event);

	void SetStartingStateStandard(wxCommandEvent& event);
	void SetStartingStateExcited(wxCommandEvent& event);
	void SetStartingStateBoth(wxCommandEvent& event);

	void FindPatterns(wxCommandEvent& event);

public:

	GetSingleJugglerPatternsWindow(wxWindow* parent);
	virtual ~GetSingleJugglerPatternsWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
