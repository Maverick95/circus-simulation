#include <wx\spinctrl.h>

#include "NumberSitesSettingsWindow.h"

static const wxWindowID SPN_NUMBER_SITES = 1;

static const unsigned int ACTION_NUMBER_SITES = 1U;

void NumberSitesSettingsWindow::NumberSites(wxSpinEvent& event)
{
	GetEventGenerator()->SetNumberSites(event.GetPosition());
	GenerateEventsForSource(event);
}

wxBEGIN_EVENT_TABLE(NumberSitesSettingsWindow, SettingsWindow<SettingsMappers::NumberSitesMapper>)

EVT_SPINCTRL(SPN_NUMBER_SITES, NumberSitesSettingsWindow::NumberSites)

wxEND_EVENT_TABLE()

NumberSitesSettingsWindow::NumberSitesSettingsWindow(wxWindow* parent)
	: SettingsWindow<SettingsMappers::NumberSitesMapper>(parent)
{
	wxSpinCtrl* spnNumberSites = new wxSpinCtrl(
		this, SPN_NUMBER_SITES, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		16384L, 1, 15, 3);

	GetEventGenerator()->SetNumberSites(3U);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(spnNumberSites, 1, wxEXPAND);
	SetSizer(sizer);

	MapControlToAction(SPN_NUMBER_SITES, ACTION_NUMBER_SITES);
	MapActionToEvent(ACTION_NUMBER_SITES, &SettingsMappers::NumberSitesMapper::CreateNumberSitesEvent);
}

NumberSitesSettingsWindow::~NumberSitesSettingsWindow()
{

}