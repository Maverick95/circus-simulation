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
}

wxDECLARE_EVENT(SET_COLOUR, SettingsEvents::SetColourEvent);

#define EVT_SET_COLOUR(func) wx__DECLARE_EVT0(SET_COLOUR, &func)



#endif
