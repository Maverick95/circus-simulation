#include "GetSingleJugglerPatternsWindow.h"

#include <wx/spinctrl.h>


GetSingleJugglerPatternsWindow::GetSingleJugglerPatternsWindow(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
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
	wxStaticText* st_maxThrowHeight = new wxStaticText(this, wxID_ANY, "Max throw height :");

	wxSpinCtrl* sp_numberBalls = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, 
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		0, 100);

	wxSpinCtrl* sp_numberThrows = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		0, 100);

	wxSpinCtrl* sp_maxThrowHeight = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		0, 100);

	wxSizerFlags st_flags = wxSizerFlags().Center();
	wxSizerFlags sp_flags = wxSizerFlags().Expand();

	sz_0_g->Add(st_numberBalls, st_flags);
	sz_0_g->Add(sp_numberBalls, sp_flags);

	sz_0_g->Add(st_numberThrows, st_flags);
	sz_0_g->Add(sp_numberThrows, sp_flags);
	
	sz_0_g->Add(st_maxThrowHeight, st_flags);
	sz_0_g->Add(sp_maxThrowHeight, sp_flags);

	sz->Add(sz_0_g, 1, wxEXPAND);

	// Section 2.

	wxBoxSizer* sz_1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sz_1_v = new wxBoxSizer(wxVERTICAL);

	wxStaticText* st_patternTypeHeader = new wxStaticText(this, wxID_ANY, "Pattern type");

	wxRadioButton* rd_patternTypeAsync = new wxRadioButton(
		this, wxID_ANY, "Asynchronous",
		wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

	wxRadioButton* rd_patternTypeSync = new wxRadioButton(
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

	wxRadioButton* rd_startingStateStandard = new wxRadioButton(
		this, wxID_ANY, "Standard",
		wxDefaultPosition, wxDefaultSize, wxRB_GROUP);

	wxRadioButton* rd_startingStateExcited = new wxRadioButton(
		this, wxID_ANY, "Excited");

	wxRadioButton* rd_startingStateBoth = new wxRadioButton(
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
}

GetSingleJugglerPatternsWindow::~GetSingleJugglerPatternsWindow()
{

}