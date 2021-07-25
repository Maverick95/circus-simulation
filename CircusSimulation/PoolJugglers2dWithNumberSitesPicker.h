#ifndef POOL_JUGGLERS_2D_WITH_NUMBER_SITES_PICKER_H
#define POOL_JUGGLERS_2D_WITH_NUMBER_SITES_PICKER_H

#include <wx\wx.h>

#include "PoolJugglers2dWindow.h"

class PoolJugglers2dWithNumberSitesPicker : public wxWindow
{

private:

	PoolJugglers2dWindow* displayPatternWindow;

public:

	PoolJugglers2dWithNumberSitesPicker(wxWindow* parent);
	virtual ~PoolJugglers2dWithNumberSitesPicker();

	DisplayPatternWindow* GetDisplayPatternWindow();

};

#endif
