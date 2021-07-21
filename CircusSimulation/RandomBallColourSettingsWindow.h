#ifndef RANDOM_BALL_COLOUR_SETTINGS_WINDOW_H
#define RANDOM_BALL_COLOUR_SETTINGS_WINDOW_H

#include <wx\wx.h>

#include "SettingsWindow.h"
#include "SettingsMappers.h"

class RandomBallColourSettingsWindow : public SettingsWindow<SettingsMappers::RandomBallColourMapper>
{

private:

	void DoClick(wxCommandEvent& event);

public:

	RandomBallColourSettingsWindow(wxWindow* parent);
	virtual ~RandomBallColourSettingsWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
