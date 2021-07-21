#include <wx\spinctrl.h>

#include "Settings.h"
#include "SingleJugglerWithRandomColourPicker.h"
#include "PoolJugglers2dWindow.h"

#include "CircusSimulationFrame.h"
#include "SiteswapGraph.h"

#include "GetSingleJugglerPatternsWindow.h"



static const int WINDOW_SINGLE_JUGGLER_PATTERNS = 1;



wxBEGIN_EVENT_TABLE(CircusSimulationFrame, wxFrame)

EVT_MENU(wxID_EXIT, CircusSimulationFrame::OnExit)
EVT_SIZE(CircusSimulationFrame::Resize)
EVT_COMMAND(WINDOW_SINGLE_JUGGLER_PATTERNS, POPULATE_PATTERN_EVENT, PopulateFromSingleJugglerPatternsWindow)

wxEND_EVENT_TABLE()



void CircusSimulationFrame::OnExit(wxCommandEvent & event)
{
	Close(true);
}

void CircusSimulationFrame::PopulateFromSingleJugglerPatternsWindow(wxCommandEvent& event)
{
	pattern_handler.Populate(*(SiteswapPattern*)(event.GetClientData()));
	Resize_Internal();
}

void CircusSimulationFrame::Resize_Internal()
{
	Layout();
	pattern_handler.Layout();
}

void CircusSimulationFrame::Resize(wxSizeEvent & e)
{
	Resize_Internal();
}

CircusSimulationFrame::CircusSimulationFrame(const wxString & title, const wxPoint & pos, const wxSize & size)
	: wxFrame(NULL, wxID_ANY, title, pos, size),
	pattern_handler(this),
	window_1(NULL),
	window_2(NULL)
{
	// Obtain the starting window client size settings and use this to set the horizontal sizes.

	const wxSize& ws_initial = Settings::WindowSize_Initial();

	wxBoxSizer * sz_0 = new wxBoxSizer(wxHORIZONTAL);

	window_1 = new SingleJugglerWithRandomColourPicker(this);
	window_2 = new PoolJugglers2dWindow(this, 3U);
	
	GetSingleJugglerPatternsWindow* window_3 = new GetSingleJugglerPatternsWindow(this, WINDOW_SINGLE_JUGGLER_PATTERNS);

	pattern_handler.AddWindow(window_1->GetDisplayPatternWindow());
	pattern_handler.AddWindow(window_2);

	wxBoxSizer* sz_1 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer * sz_1_1 = new wxBoxSizer(wxHORIZONTAL);
	sz_1_1->Add(window_1, 1, wxEXPAND);

	sz_1_1->Add(window_2, 1, wxEXPAND);
	
	sz_1->Add(sz_1_1, 1, wxEXPAND);
	sz_1->Add(&pattern_handler);
	
	sz_0->Add(sz_1, 5, wxEXPAND);
	sz_0->Add(window_3, 1, wxEXPAND);

	SetSizer(sz_0);
	SetClientSize(ws_initial);
	
	Resize_Internal();
}

CircusSimulationFrame::~CircusSimulationFrame()
{
	delete window_1;
	delete window_2;
}

