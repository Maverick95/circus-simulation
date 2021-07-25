#ifndef SETTINGS_MAPPERS_H
#define SETTINGS_MAPPERS_H

#include <wx\wx.h>

#include "SettingsEvents.h"

namespace SettingsMappers
{
	class RandomColourMapper
	{

	public:

		RandomColourMapper();
		virtual ~RandomColourMapper();

		wxEvent* CreateRandomColourEvent(const wxWindowID& window);

	};

	class NumberSitesMapper
	{

	private:

		unsigned int numberSites;

	public:

		NumberSitesMapper();
		virtual ~NumberSitesMapper();

		void SetNumberSites(const unsigned int& s);

		wxEvent* CreateNumberSitesEvent(const wxWindowID& window);

	};
}

#endif
