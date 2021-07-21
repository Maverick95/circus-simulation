#include "SettingsEvents.h"

wxDEFINE_EVENT(SET_COLOUR, SettingsEvents::SetColourEvent);

SettingsEvents::SetColourEvent::SetColourEvent(
	wxEventType eventType,
	wxWindowID winid,
	const int& r,
	const int& g,
	const int& b)
	: wxEvent(winid, eventType),
	red(r % 256), green(g % 256), blue(b % 256)
{

}

SettingsEvents::SetColourEvent::~SetColourEvent()
{

}

wxEvent* SettingsEvents::SetColourEvent::Clone() const
{
	return new SettingsEvents::SetColourEvent(*this);
}

int SettingsEvents::SetColourEvent::Red() const
{
	return red;
}

int SettingsEvents::SetColourEvent::Green() const
{
	return green;
}

int SettingsEvents::SetColourEvent::Blue() const
{
	return blue;
}

