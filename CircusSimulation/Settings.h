#ifndef SETTINGS_H
#define SETTINGS_H

#include "stdafx.h"

#include <wx\wx.h>

#include "Enum.h"

namespace Settings
{
	unsigned int NumberBalls_Minimum();
	unsigned int NumberBalls_Maximum();
	unsigned int NumberThrows_Maximum();
	unsigned int ThrowHeight_Maximum();

	const wxSize& WindowSize_Initial();

	unsigned int ScreenUpdates_PerSecond();
	unsigned int Milliseconds_PerScreenUpdate();

	const double * DisplayPattern_Padding();

	long Pattern_BeatTime_Milliseconds();
	double Pattern_BeatTime_Increase_MultiFactor();

	unsigned int Pattern_MaxHeight_Pixels();
	unsigned int Pattern_MaxWidth_Pixels();

	SiteswapGraphShortestPathMethod SiteswapGraph_ShortestPathMethod();
}

#endif
