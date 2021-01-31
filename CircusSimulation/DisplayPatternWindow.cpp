#include "DisplayPatternHandler.h"
#include "Settings.h"

#include "DisplayPatternWindow.h"



static const int TIMER_SCREEN_UPDATE = 1;



wxBEGIN_EVENT_TABLE(DisplayPatternWindow, wxWindow)

EVT_TIMER(TIMER_SCREEN_UPDATE, DisplayPatternWindow::OnScreenUpdate)
EVT_PAINT(DisplayPatternWindow::OnScreenPaint)

wxEND_EVENT_TABLE()



void DisplayPatternWindow::OnScreenUpdate(wxTimerEvent& event)
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		// Immediately obtain the current time elapsed since the last beat.

		long time_elapsed = handler->GetStopwatch();

		// Apply any derived additional functionality.

		OnScreenUpdate_Derived(time_elapsed);

		// Update screen - note that all screen won't automatically need refreshing
		// derived functionality invalidates the area.

		Update();
	}
}

void DisplayPatternWindow::OnBallsUpdate()
{
	OnBallsUpdate_Derived();
}

void DisplayPatternWindow::OnScreenPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);

	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	auto h = GetValidHandler();

	if (h != NULL)
	{
		// Apply any derived additional functionality.

		OnScreenPaint_Derived(dc);
	}
}

DisplayPatternHandler * DisplayPatternWindow::GetValidHandler()
{
	DisplayPatternHandler * return_value = NULL;

	if (handler != NULL)
	{
		if (handler->IsValid())
		{
			return_value = handler;
		}
	}

	return return_value;
}


DisplayPatternWindow::DisplayPatternWindow(wxWindow * parent)
	: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0L),
	handler(NULL),
	timer_update_screen(NULL),
	full_removal(true)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
}

DisplayPatternWindow::~DisplayPatternWindow()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		delete timer_update_screen;
	}

	// Need to remove link from the handler.

	if (handler != NULL)
	{
		full_removal = false;
		handler->RemoveWindow(this);
	}
}

void DisplayPatternWindow::Reset()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		delete timer_update_screen;
	}

	timer_update_screen = NULL;

	Reset_Derived();
}

void DisplayPatternWindow::Populate()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		timer_update_screen = new wxTimer(this, TIMER_SCREEN_UPDATE);
	}

	Populate_Derived();
}



// Control functions.



void DisplayPatternWindow::Play()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		timer_update_screen->Start(Settings::Milliseconds_PerScreenUpdate());
	}
}

void DisplayPatternWindow::Stop()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		timer_update_screen->Stop();
	}

	Stop_Derived();
}
