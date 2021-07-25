#include "SettingsEvents.h"



wxDEFINE_EVENT(SET_COLOUR, SettingsEvents::SetColourEvent);
wxDEFINE_EVENT(SET_NUMBER_SITES, SettingsEvents::SetNumberSitesEvent);



using namespace SettingsEvents;



SetColourEvent::SetColourEvent(
	wxEventType eventType,
	wxWindowID winid,
	const int& r,
	const int& g,
	const int& b)
	: wxEvent(winid, eventType),
	red(r % 256), green(g % 256), blue(b % 256)
{

}

SetColourEvent::~SetColourEvent()
{

}

wxEvent* SetColourEvent::Clone() const
{
	return new SetColourEvent(*this);
}

int SetColourEvent::Red() const
{
	return red;
}

int SetColourEvent::Green() const
{
	return green;
}

int SetColourEvent::Blue() const
{
	return blue;
}



SetNumberSitesEvent::SetNumberSitesEvent(
	wxEventType eventType,
	wxWindowID winid,
	const unsigned int& s)
	: wxEvent(winid, eventType),
	numberSites(s == 0U ? 1U : s)
{

}

SetNumberSitesEvent::~SetNumberSitesEvent()
{

}

wxEvent* SetNumberSitesEvent::Clone() const
{
	return new SetNumberSitesEvent(*this);
}

unsigned int SetNumberSitesEvent::NumberSites() const
{
	return numberSites;
}

