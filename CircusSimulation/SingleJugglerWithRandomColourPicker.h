#ifndef SINGLE_JUGGLER_WITH_RANDOM_COLOUR_PICKER_H
#define SINGLE_JUGGLER_WITH_RANDOM_COLOUR_PICKER_H

#include <wx\wx.h>

#include "SingleJugglerWindow.h"

class SingleJugglerWithRandomColourPicker : public wxWindow
{

private:

	SingleJugglerWindow* displayPatternWindow;

public:

	SingleJugglerWithRandomColourPicker(wxWindow* parent);
	virtual ~SingleJugglerWithRandomColourPicker();

	DisplayPatternWindow* GetDisplayPatternWindow();

};

#endif
