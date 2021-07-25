#include <cstdlib>

#include "SettingsEvents.h"
#include "SettingsMappers.h"



using namespace SettingsMappers;


RandomColourMapper::RandomColourMapper()
{

}

RandomColourMapper::~RandomColourMapper()
{

}

wxEvent* RandomColourMapper::CreateRandomColourEvent(const wxWindowID& window)
{
	srand(time(NULL));
	return new SettingsEvents::SetColourEvent(SET_COLOUR, window, rand(), rand(), rand());
}



NumberSitesMapper::NumberSitesMapper()
	: numberSites(1U)
{

}

NumberSitesMapper::~NumberSitesMapper()
{

}

void NumberSitesMapper::SetNumberSites(const unsigned int& s)
{
	numberSites = s == 0U ? 1U : s;
}

wxEvent* NumberSitesMapper::CreateNumberSitesEvent(const wxWindowID& window)
{
	return new SettingsEvents::SetNumberSitesEvent(SET_NUMBER_SITES, window, numberSites);
}

