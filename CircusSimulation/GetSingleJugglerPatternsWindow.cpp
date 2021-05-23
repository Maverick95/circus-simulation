#include "GetSingleJugglerPatternsWindow.h"

#include <wx/spinctrl.h>


GetSingleJugglerPatternsWindow::GetSingleJugglerPatternsWindow(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
{
	wxFlexGridSizer* sz_0 = new wxFlexGridSizer(3, 2, 0, 0);
	sz_0->SetFlexibleDirection(wxBOTH);
	sz_0->AddGrowableCol(0);
	sz_0->AddGrowableCol(1);

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

	sz_0->Add(st_numberBalls, st_flags);
	sz_0->Add(sp_numberBalls, sp_flags);

	sz_0->Add(st_numberThrows, st_flags);
	sz_0->Add(sp_numberThrows, sp_flags);
	
	sz_0->Add(st_maxThrowHeight, st_flags);
	sz_0->Add(sp_maxThrowHeight, sp_flags);

	SetSizer(sz_0);
}

GetSingleJugglerPatternsWindow::~GetSingleJugglerPatternsWindow()
{

}