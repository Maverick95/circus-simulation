#ifndef NUMBER_SITES_SETTINGS_WINDOW_H
#define NUMBER_SITES_SETTINGS_WINDOW_H

#include <wx\wx.h>

#include "SettingsWindow.h"
#include "SettingsMappers.h"

class NumberSitesSettingsWindow : public SettingsWindow<SettingsMappers::NumberSitesMapper>
{

private:

	void NumberSites(wxSpinEvent& event);

public:

	NumberSitesSettingsWindow(wxWindow* parent);
	virtual ~NumberSitesSettingsWindow();

	wxDECLARE_EVENT_TABLE();

};

#endif
