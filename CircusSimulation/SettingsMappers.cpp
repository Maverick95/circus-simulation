#include <cstdlib>

#include "SettingsEvents.h"
#include "SettingsMappers.h"

SettingsMappers::RandomBallColourMapper::RandomBallColourMapper()
{

}

SettingsMappers::RandomBallColourMapper::~RandomBallColourMapper()
{

}

wxEvent* SettingsMappers::RandomBallColourMapper::GetRandomColour(const wxWindowID& window)
{
	srand(time(NULL));
	wxEvent* newEvent = new SettingsEvents::SetColourEvent(SET_COLOUR, window, rand(), rand(), rand());
	return newEvent;
}
