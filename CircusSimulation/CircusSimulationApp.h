#ifndef CIRCUS_SIMULATION_APP_H
#define CIRCUS_SIMULATION_APP_H

#include "stdafx.h"

#include <wx\wx.h>

class CircusSimulationApp : public wxApp
{

public:

	virtual bool OnInit();
	virtual int OnExit();

	CircusSimulationApp();

};

#endif
