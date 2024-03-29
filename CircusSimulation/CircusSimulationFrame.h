#ifndef CIRCUS_SIMULATION_FRAME_H
#define CIRCUS_SIMULATION_FRAME_H

#include "stdafx.h"

#include <wx\wx.h>

#include "Struct.h"

#include "DisplayPatternHandler.h"
#include "DisplayPatternWindow.h"
#include "SingleJugglerWithRandomColourPicker.h"
#include "PoolJugglers2dWithNumberSitesPicker.h"

class CircusSimulationFrame : public wxFrame
{

private:

	DisplayPatternHandler pattern_handler;

	SingleJugglerWithRandomColourPicker* window_1;
	PoolJugglers2dWithNumberSitesPicker* window_2;

	void OnExit(wxCommandEvent &);

	void PopulateFromSingleJugglerPatternsWindow(wxCommandEvent& event);

	void Resize_Internal();
	void Resize(wxSizeEvent &);

	wxDECLARE_EVENT_TABLE();

public:

	CircusSimulationFrame(const wxString &, const wxPoint &, const wxSize &);

	virtual ~CircusSimulationFrame();

};


#endif
