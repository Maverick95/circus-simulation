#ifndef SETTINGS_EVENTS_H
#define SETTINGS_EVENTS_H

#include <wx\wx.h>

namespace SettingsEvents
{
	class SetColourEvent : public wxEvent
	{

	private:

		int red, green, blue;

	public:

		SetColourEvent(
			wxEventType eventType,
			wxWindowID winid,
			const int& r,
			const int& g,
			const int& b);
		
		virtual ~SetColourEvent();

		virtual wxEvent* Clone() const;

		int Red() const;
		int Green() const;
		int Blue() const;

	};

	class SetNumberSitesEvent : public wxEvent
	{

	private:

		unsigned int numberSites;

	public:

		SetNumberSitesEvent(
			wxEventType eventType,
			wxWindowID winid,
			const unsigned int& s);

		virtual ~SetNumberSitesEvent();

		virtual wxEvent* Clone() const;

		unsigned int NumberSites() const;
		
	};
}

wxDECLARE_EVENT(SET_COLOUR, SettingsEvents::SetColourEvent);
wxDECLARE_EVENT(SET_NUMBER_SITES, SettingsEvents::SetNumberSitesEvent);

#define EVT_SET_COLOUR(func) wx__DECLARE_EVT0(SET_COLOUR, &func)
#define EVT_SET_NUMBER_SITES(func) wx__DECLARE_EVT0(SET_NUMBER_SITES, &func)

#endif
