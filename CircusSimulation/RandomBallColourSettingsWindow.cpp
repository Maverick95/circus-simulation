#include "RandomBallColourSettingsWindow.h"

static const wxWindowID BTN_RANDOM_BALL_COLOUR = 1;

static const unsigned int ACTION_RANDOM_COLOUR = 1U;

void RandomBallColourSettingsWindow::RandomBallColour(wxCommandEvent& event)
{
	GenerateEventsForSource(event);
}

wxBEGIN_EVENT_TABLE(RandomBallColourSettingsWindow, SettingsWindow<SettingsMappers::RandomColourMapper>)

EVT_BUTTON(BTN_RANDOM_BALL_COLOUR, RandomBallColourSettingsWindow::RandomBallColour)

wxEND_EVENT_TABLE()

RandomBallColourSettingsWindow::RandomBallColourSettingsWindow(wxWindow* parent)
	: SettingsWindow<SettingsMappers::RandomColourMapper>(parent)
{
	wxButton* btnRandomBallColour = new wxButton(this, BTN_RANDOM_BALL_COLOUR, "Random Ball Colour");
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(btnRandomBallColour, 1, wxEXPAND);
	SetSizer(sizer);

	MapControlToAction(BTN_RANDOM_BALL_COLOUR, ACTION_RANDOM_COLOUR);
	MapActionToEvent(ACTION_RANDOM_COLOUR, &SettingsMappers::RandomColourMapper::CreateRandomColourEvent);
}

RandomBallColourSettingsWindow::~RandomBallColourSettingsWindow()
{

}
