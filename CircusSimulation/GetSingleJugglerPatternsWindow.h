#ifndef GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H
#define GET_SINGLE_JUGGLER_PATTERNS_WINDOW_H

#include "Enum.h"
#include "Struct.h"

#include <set>

#include <wx\wx.h>
#include <wx\listctrl.h>

wxDECLARE_EVENT(POPULATE_PATTERN_EVENT, wxCommandEvent);

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

	std::set<SiteswapPattern>* patterns;

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

	void PopulatePattern(wxListEvent& event);

public:

	GetSingleJugglerPatternsWindow(wxWindow* parent, int id);
	virtual ~GetSingleJugglerPatternsWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
