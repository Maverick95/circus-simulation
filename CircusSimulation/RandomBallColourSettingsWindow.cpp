#include "RandomBallColourSettingsWindow.h"

static const int click_button = 1;

void RandomBallColourSettingsWindow::DoClick(wxCommandEvent& event)
{
	GenerateEventsForSource(event);
}

wxBEGIN_EVENT_TABLE(RandomBallColourSettingsWindow, SettingsWindow<SettingsMappers::RandomBallColourMapper>)

EVT_BUTTON(click_button, DoClick)

wxEND_EVENT_TABLE()

RandomBallColourSettingsWindow::RandomBallColourSettingsWindow(wxWindow* parent)
	: SettingsWindow<SettingsMappers::RandomBallColourMapper>(parent)
{
	wxButton* btn1 = new wxButton(this, click_button, "Test this");

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(btn1, 1, wxEXPAND);

	SetSizer(sizer);

	MapControlToAction(click_button, 1U);
	MapActionToEvent(1U, &SettingsMappers::RandomBallColourMapper::GetRandomColour);
}

RandomBallColourSettingsWindow::~RandomBallColourSettingsWindow()
{

}
