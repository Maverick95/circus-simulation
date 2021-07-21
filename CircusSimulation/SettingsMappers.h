#ifndef SETTINGS_MAPPERS_H
#define SETTINGS_MAPPERS_H

#include <wx\wx.h>

#include "SettingsEvents.h"

namespace SettingsMappers
{
	class RandomBallColourMapper
	{

	public:

		RandomBallColourMapper();
		virtual ~RandomBallColourMapper();

		wxEvent* GetRandomColour(const wxWindowID& window);

	};
}

#endif
