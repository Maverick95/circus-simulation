#include "GetSingleJugglerPatternsWindow.h"

#include <wx/spinctrl.h>


GetSingleJugglerPatternsWindow::GetSingleJugglerPatternsWindow(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
{
	wxFlexGridSizer* sz_0 = new wxFlexGridSizer(3, 2, 0, 0);
	
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


	sz_0->Add(st_numberBalls);
	sz_0->Add(sp_numberBalls);

	sz_0->Add(st_numberThrows);
	sz_0->Add(sp_numberThrows);
	
	sz_0->Add(st_maxThrowHeight);
	sz_0->Add(sp_maxThrowHeight);

	SetSizer(sz_0);
}

GetSingleJugglerPatternsWindow::~GetSingleJugglerPatternsWindow()
{

}