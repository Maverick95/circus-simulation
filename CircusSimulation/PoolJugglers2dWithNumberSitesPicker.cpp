#include "PoolJugglers2dWithNumberSitesPicker.h"

#include "NumberSitesSettingsWindow.h"

PoolJugglers2dWithNumberSitesPicker::PoolJugglers2dWithNumberSitesPicker(wxWindow* parent)
	: wxWindow(parent, wxID_ANY),
	displayPatternWindow(NULL)
{

	displayPatternWindow = new PoolJugglers2dWindow(this, 3U);
	auto* windowNumberSites = new NumberSitesSettingsWindow(this);

	windowNumberSites->AddWindow(displayPatternWindow);

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* sizer1 = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(displayPatternWindow, 1, wxEXPAND);
	sizer1->Add(windowNumberSites, 1, wxEXPAND);
	sizer->Add(sizer1);

	SetSizer(sizer);
}

PoolJugglers2dWithNumberSitesPicker::~PoolJugglers2dWithNumberSitesPicker()
{

}

DisplayPatternWindow* PoolJugglers2dWithNumberSitesPicker::GetDisplayPatternWindow()
{
	return displayPatternWindow;
}