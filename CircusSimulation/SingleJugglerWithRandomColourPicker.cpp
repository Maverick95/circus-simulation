#include "SingleJugglerWithRandomColourPicker.h"

#include "RandomBallColourSettingsWindow.h"

SingleJugglerWithRandomColourPicker::SingleJugglerWithRandomColourPicker(wxWindow* parent)
	: wxWindow(parent, wxID_ANY),
	displayPatternWindow(NULL)
{
	unsigned int singleJugglerRatioX[3];
	unsigned int singleJugglerRatioY[4];

	singleJugglerRatioX[0] = 3u;	singleJugglerRatioY[0] = 2u;
	singleJugglerRatioX[1] = 5u;	singleJugglerRatioY[1] = 2u;
	singleJugglerRatioX[2] = 1u;	singleJugglerRatioY[2] = 7u;
									singleJugglerRatioY[3] = 1u;

	displayPatternWindow = new SingleJugglerWindow(this, &(singleJugglerRatioX[0]), &(singleJugglerRatioY[0]), 0.4);
	auto* windowRandomBallColour = new RandomBallColourSettingsWindow(this);

	windowRandomBallColour->AddWindow(displayPatternWindow);

	auto* sizer = new wxBoxSizer(wxVERTICAL);
	auto* sizer1 = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(displayPatternWindow, 1, wxEXPAND);
	sizer1->Add(windowRandomBallColour, 1, wxEXPAND);
	sizer->Add(sizer1);

	SetSizer(sizer);
}

SingleJugglerWithRandomColourPicker::~SingleJugglerWithRandomColourPicker()
{

}

DisplayPatternWindow* SingleJugglerWithRandomColourPicker::GetDisplayPatternWindow()
{
	return displayPatternWindow;
}