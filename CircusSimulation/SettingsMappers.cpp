#include <cstdlib>

#include "SettingsEvents.h"
#include "SettingsMappers.h"

SettingsMappers::RandomColourMapper::RandomColourMapper()
{

}

SettingsMappers::RandomColourMapper::~RandomColourMapper()
{

}

wxEvent* SettingsMappers::RandomColourMapper::CreateRandomColourEvent(const wxWindowID& window)
{
	srand(time(NULL));
	return new SettingsEvents::SetColourEvent(SET_COLOUR, window, rand(), rand(), rand());
}
