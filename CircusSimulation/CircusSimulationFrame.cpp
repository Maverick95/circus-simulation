#include <wx\spinctrl.h>

#include "Settings.h"
#include "BallStatusWindow.h"
#include "SingleJugglerWindow.h"
#include "PoolJugglers2dWindow.h"

#include "CircusSimulationFrame.h"
#include "SiteswapGraph.h"

#include "GetSingleJugglerPatternsWindow.h"



static const int WINDOW_SINGLE_JUGGLER_PATTERNS = 1;



wxBEGIN_EVENT_TABLE(CircusSimulationFrame, wxFrame)

EVT_MENU(1, CircusSimulationFrame::OnHello)
EVT_MENU(wxID_EXIT, CircusSimulationFrame::OnExit)
EVT_MENU(wxID_ABOUT, CircusSimulationFrame::OnAbout)
EVT_SIZE(CircusSimulationFrame::Resize)
EVT_COMMAND(WINDOW_SINGLE_JUGGLER_PATTERNS, POPULATE_PATTERN_EVENT, PopulateFromSingleJugglerPatternsWindow)

wxEND_EVENT_TABLE()



void CircusSimulationFrame::OnExit(wxCommandEvent & event)
{
	Close(true);
}

void CircusSimulationFrame::OnAbout(wxCommandEvent & event)
{
	wxMessageBox("This is a wxWidgets' Hello world sample",
		"About Hello World", wxOK | wxICON_INFORMATION);
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

void CircusSimulationFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

CircusSimulationFrame::CircusSimulationFrame(const wxString & title, const wxPoint & pos, const wxSize & size)
	: wxFrame(NULL, wxID_ANY, title, pos, size),
	pattern_handler(this),
	window_1(NULL),
	window_2(NULL)
{
	// Obtain the starting window client size settings and use this to set the horizontal sizes.

	const wxSize& ws_initial = Settings::WindowSize_Initial();

	wxBoxSizer * sz_0 = new wxBoxSizer(wxVERTICAL);

	// Set up values for ball drawing window sizing.

	unsigned int window_ratios_x[3];
	unsigned int window_ratios_y[4];

	window_ratios_x[0] = 3u; window_ratios_x[1] = 5u; window_ratios_x[2] = 1u;
	window_ratios_y[0] = 2u; window_ratios_y[1] = 2u; window_ratios_y[2] = 7u; window_ratios_y[3] = 1u;

	//window_1 = new SingleJugglerWindow(this, &(window_ratios_x[0]), &(window_ratios_y[0]), 0.4);
	window_1 = new PoolJugglers2dWindow(this, 3U);
	window_2 = new BallStatusWindow(this);
	
	GetSingleJugglerPatternsWindow* window_3 = new GetSingleJugglerPatternsWindow(this, WINDOW_SINGLE_JUGGLER_PATTERNS);

	pattern_handler.AddWindow(window_1);
	pattern_handler.AddWindow(window_2);

	wxBoxSizer * sz_1_1 = new wxBoxSizer(wxHORIZONTAL);

	sz_1_1->Add(window_1, 1, wxEXPAND);
	sz_1_1->Add(window_2, 1, wxEXPAND);
	sz_1_1->Add(window_3, 1, wxEXPAND);

	sz_0->Add(sz_1_1, 5, wxEXPAND);

	wxBoxSizer * sz_1_2 = new wxBoxSizer(wxHORIZONTAL);

	sz_0->Add(sz_1_2, 1, wxEXPAND);

	sz_0->Add(&pattern_handler);

	SetSizer(sz_0);
	SetClientSize(ws_initial);
	
	Resize_Internal();
}

CircusSimulationFrame::~CircusSimulationFrame()
{
	delete window_1;
	delete window_2;
}

