#include "GetSingleJugglerPatternsWindow.h"
#include "Settings.h"

#include <wx/spinctrl.h>



/* Window IDs. */

static const unsigned int ID_SPIN_NUMBER_BALLS = 1U;

static const unsigned int ID_RADIO_TYPE_ASYNC = 2U;
static const unsigned int ID_RADIO_TYPE_SYNC = 3U;

static const unsigned int ID_RADIO_STARTING_STATE_STANDARD = 4U;
static const unsigned int ID_RADIO_STARTING_STATE_EXCITED = 4U;
static const unsigned int ID_RADIO_STARTING_STATE_BOTH = 4U;



/* Event table. */

BEGIN_EVENT_TABLE(GetSingleJugglerPatternsWindow, wxWindow)

EVT_SPINCTRL(ID_SPIN_NUMBER_BALLS, SetThrowHeightMaxBoundaries)

EVT_RADIOBUTTON(ID_RADIO_TYPE_ASYNC, SetTypeAsync)
EVT_RADIOBUTTON(ID_RADIO_TYPE_SYNC, SetTypeSync)

EVT_RADIOBUTTON(ID_RADIO_STARTING_STATE_STANDARD, SetStartingStateStandard)
EVT_RADIOBUTTON(ID_RADIO_STARTING_STATE_EXCITED, SetStartingStateExcited)
EVT_RADIOBUTTON(ID_RADIO_STARTING_STATE_BOTH, SetStartingStateBoth)

END_EVENT_TABLE()



void GetSingleJugglerPatternsWindow::SetRadioButtonStatuses()
{
	switch (type)
	{
	case PatternQuerySingleJugglerType::TYPE_ASYNC:
		rd_patternTypeAsync->SetValue(true);
		break;
	case PatternQuerySingleJugglerType::TYPE_SYNC:
		rd_patternTypeSync->SetValue(true);
		break;
	}

	switch (startingState)
	{
	case PatternQueryStartingState::STATE_STANDARD_ONLY:
		rd_startingStateStandard->SetValue(true);
		break;
	case PatternQueryStartingState::STATE_EXCITED_ONLY:
		rd_startingStateExcited->SetValue(true);
		break;
	case PatternQueryStartingState::STATE_ALL:
		rd_startingStateBoth->SetValue(true);
		break;
	}
}



void GetSingleJugglerPatternsWindow::SetThrowHeightMaxBoundaries(wxSpinEvent& event)
{
	const unsigned int
		settings_numberBallsMin = event.GetPosition(),
		settings_throwHeightMax = Settings::ThrowHeight_Maximum();

	sp_throwHeightMax->SetRange(settings_numberBallsMin,
		settings_throwHeightMax < settings_numberBallsMin ? settings_numberBallsMin : settings_throwHeightMax);
}



void GetSingleJugglerPatternsWindow::SetTypeAsync(wxCommandEvent& event)
{
	type = PatternQuerySingleJugglerType::TYPE_ASYNC;
}

void GetSingleJugglerPatternsWindow::SetTypeSync(wxCommandEvent& event)
{
	type = PatternQuerySingleJugglerType::TYPE_SYNC;
}

void GetSingleJugglerPatternsWindow::SetStartingStateStandard(wxCommandEvent& event)
{
	startingState = PatternQueryStartingState::STATE_STANDARD_ONLY;
}

void GetSingleJugglerPatternsWindow::SetStartingStateExcited(wxCommandEvent& event)
{
	startingState = PatternQueryStartingState::STATE_EXCITED_ONLY;
}

void GetSingleJugglerPatternsWindow::SetStartingStateBoth(wxCommandEvent& event)
{
	startingState = PatternQueryStartingState::STATE_ALL;
}



GetSingleJugglerPatternsWindow::GetSingleJugglerPatternsWindow(wxWindow* parent)
	: wxWindow(parent, wxID_ANY),
	sp_numberBalls(NULL),
	sp_numberThrows(NULL),
	sp_throwHeightMax(NULL),
	rd_patternTypeAsync(NULL),
	rd_patternTypeSync(NULL),
	rd_startingStateStandard(NULL),
	rd_startingStateExcited(NULL),
	rd_startingStateBoth(NULL),
	type(PatternQuerySingleJugglerType::TYPE_SYNC),
	startingState(PatternQueryStartingState::STATE_EXCITED_ONLY)
{
	wxBoxSizer* sz_base = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* sz = new wxBoxSizer(wxVERTICAL);

	// Section 1.

	wxFlexGridSizer* sz_0_g = new wxFlexGridSizer(3, 2, 0, 0);
	sz_0_g->SetFlexibleDirection(wxBOTH);
	sz_0_g->AddGrowableCol(0);
	sz_0_g->AddGrowableCol(1);

	wxStaticText* st_numberBalls = new wxStaticText(this, wxID_ANY, "Balls in pattern :");
	wxStaticText* st_numberThrows = new wxStaticText(this, wxID_ANY, "Throws in pattern :");
	wxStaticText* st_throwHeightMax = new wxStaticText(this, wxID_ANY, "Max throw height :");

	const unsigned int
		settings_numberBallsMin = Settings::NumberBalls_Minimum(),
		settings_numberBallsMax = Settings::NumberBalls_Maximum(),
		settings_numberThrowsMax = Settings::NumberThrows_Maximum(),
		settings_throwHeightMax = Settings::ThrowHeight_Maximum();

	sp_numberBalls = new wxSpinCtrl(this, ID_SPIN_NUMBER_BALLS, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		settings_numberBallsMin, settings_numberBallsMax);

	sp_numberThrows = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		1U, settings_numberThrowsMax);

	sp_throwHeightMax = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		settings_numberBallsMin,
		settings_throwHeightMax < settings_numberBallsMin ? settings_numberBallsMin : settings_throwHeightMax);

	wxSizerFlags st_flags = wxSizerFlags().Center();
	wxSizerFlags sp_flags = wxSizerFlags().Expand();

	sz_0_g->Add(st_numberBalls, st_flags);
	sz_0_g->Add(sp_numberBalls, sp_flags);

	sz_0_g->Add(st_numberThrows, st_flags);
	sz_0_g->Add(sp_numberThrows, sp_flags);
	
	sz_0_g->Add(st_throwHeightMax, st_flags);
	sz_0_g->Add(sp_throwHeightMax, sp_flags);

	sz->Add(sz_0_g, 1, wxEXPAND);

	// Section 2.

	wxBoxSizer* sz_1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sz_1_v = new wxBoxSizer(wxVERTICAL);

	wxStaticText* st_patternTypeHeader = new wxStaticText(this, wxID_ANY, "Pattern type");

	rd_patternTypeAsync = new wxRadioButton(
		this, wxID_ANY, "Asynchronous",
		wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

	rd_patternTypeSync = new wxRadioButton(
		this, wxID_ANY, "Synchronous");

	sz_1->AddStretchSpacer();

	sz_1_v->AddStretchSpacer();
	sz_1_v->Add(st_patternTypeHeader, 0, wxALIGN_CENTER_HORIZONTAL);
	sz_1_v->Add(rd_patternTypeAsync);
	sz_1_v->Add(rd_patternTypeSync);
	sz_1_v->AddStretchSpacer();

	sz_1->Add(sz_1_v, 0, wxEXPAND);

	sz_1->AddStretchSpacer();

	sz->Add(sz_1, 1, wxEXPAND);

	// Section 3.

	wxBoxSizer* sz_2 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sz_2_v = new wxBoxSizer(wxVERTICAL);

	wxStaticText* st_startingStateHeader = new wxStaticText(this, wxID_ANY, "Starting state");

	rd_startingStateStandard = new wxRadioButton(
		this, wxID_ANY, "Standard",
		wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

	rd_startingStateExcited = new wxRadioButton(
		this, wxID_ANY, "Excited");

	rd_startingStateBoth = new wxRadioButton(
		this, wxID_ANY, "Both");

	sz_2->AddStretchSpacer();

	sz_2_v->AddStretchSpacer();
	sz_2_v->Add(st_startingStateHeader, 0, wxALIGN_CENTER_HORIZONTAL);
	sz_2_v->Add(rd_startingStateStandard);
	sz_2_v->Add(rd_startingStateExcited);
	sz_2_v->Add(rd_startingStateBoth);
	sz_2_v->AddStretchSpacer();

	sz_2->Add(sz_2_v, 0, wxEXPAND);

	sz_2->AddStretchSpacer();

	sz->Add(sz_2, 1, wxEXPAND);

	// Section 4.

	wxButton* bt_FindPatterns = new wxButton(
		this, wxID_ANY, "Find");

	sz->Add(bt_FindPatterns, 1, wxEXPAND);

	sz_base->Add(sz, 1, wxEXPAND);
	sz_base->AddStretchSpacer();

	SetSizer(sz_base);

	SetRadioButtonStatuses();
}

GetSingleJugglerPatternsWindow::~GetSingleJugglerPatternsWindow()
{

}