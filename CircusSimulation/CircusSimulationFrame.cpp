#include <wx\spinctrl.h>

#include "Settings.h"
#include "BallStatusWindow.h"
#include "TestBallDrawingWindow.h"

#include "CircusSimulationFrame.h"
#include "SiteswapGraph.h"



static const int SPIN_BALLS = 1;
static const int SPIN_THROWS = 2;

static const int BUTTON_RESET = 1;
static const int BUTTON_POPULATE = 2;



wxBEGIN_EVENT_TABLE(CircusSimulationFrame, wxFrame)

EVT_MENU(1, CircusSimulationFrame::OnHello)
EVT_MENU(wxID_EXIT, CircusSimulationFrame::OnExit)
EVT_MENU(wxID_ABOUT, CircusSimulationFrame::OnAbout)
EVT_SPINCTRL(SPIN_BALLS, CircusSimulationFrame::UpdateNumberBalls)
EVT_SPINCTRL(SPIN_THROWS, CircusSimulationFrame::UpdateNumberThrows)
EVT_BUTTON(BUTTON_RESET, CircusSimulationFrame::Reset)
EVT_BUTTON(BUTTON_POPULATE, CircusSimulationFrame::Populate)
EVT_SIZE(CircusSimulationFrame::Resize)

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

SiteswapPattern* CircusSimulationFrame::GetRandomPattern()
{
	return SiteswapGraph::GetRandomPattern(num_balls, 1U, num_throws, Settings::ThrowHeight_Maximum());
}

void CircusSimulationFrame::UpdateNumberBalls(wxSpinEvent & e)
{
	num_balls = e.GetPosition();
}

void CircusSimulationFrame::UpdateNumberThrows(wxSpinEvent & e)
{
	num_throws = e.GetPosition();
}

void CircusSimulationFrame::Reset(wxCommandEvent & e)
{
	pattern_handler.Reset();
}

void CircusSimulationFrame::Populate(wxCommandEvent & e)
{
	SiteswapPattern* s = GetRandomPattern();

	if (s != NULL)
	{
		pattern_handler.Populate(*s);
		delete s;
	}

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
	window_2(NULL),
	num_balls(Settings::NumberBalls_Minimum()),
	num_throws(1u)
{
	// Obtain the starting window client size settings and use this to set the horizontal sizes.

	const wxSize& ws_initial = Settings::WindowSize_Initial();

	wxBoxSizer * sz_0 = new wxBoxSizer(wxVERTICAL);

	// Set up values for ball drawing window sizing.

	unsigned int window_ratios_x[3];
	unsigned int window_ratios_y[4];

	window_ratios_x[0] = 3u; window_ratios_x[1] = 5u; window_ratios_x[2] = 1u;
	window_ratios_y[0] = 2u; window_ratios_y[1] = 2u; window_ratios_y[2] = 7u; window_ratios_y[3] = 1u;

	window_1 = new TestBallDrawingWindow(this, &(window_ratios_x[0]), &(window_ratios_y[0]), 0.4);
	window_2 = new BallStatusWindow(this);

	pattern_handler.AddWindow(window_1);
	pattern_handler.AddWindow(window_2);

	wxBoxSizer * sz_1_1 = new wxBoxSizer(wxHORIZONTAL);

	sz_1_1->Add(window_1, 1, wxEXPAND);
	sz_1_1->Add(window_2, 1, wxEXPAND);

	sz_0->Add(sz_1_1, 5, wxEXPAND);

	wxBoxSizer * sz_1_2 = new wxBoxSizer(wxHORIZONTAL);

	wxSpinCtrl * sp_1 = new wxSpinCtrl(this, SPIN_BALLS, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		Settings::NumberBalls_Minimum(), Settings::NumberBalls_Maximum(), Settings::NumberBalls_Minimum());

	wxSpinCtrl * sp_2 = new wxSpinCtrl(this, SPIN_THROWS, wxEmptyString,
		wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS,
		1u, 10u, 1u);

	wxButton * bt_1 = new wxButton(this, BUTTON_RESET, wxString("Reset"));
	wxButton * bt_2 = new wxButton(this, BUTTON_POPULATE, wxString("Populate"));

	sz_1_2->Add(sp_1, 1, wxEXPAND);
	sz_1_2->Add(sp_2, 1, wxEXPAND);
	sz_1_2->Add(bt_1, 1, wxEXPAND);
	sz_1_2->Add(bt_2, 1, wxEXPAND);

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

