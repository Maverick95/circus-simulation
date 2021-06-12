#ifndef CIRCUS_SIMULATION_FRAME_H
#define CIRCUS_SIMULATION_FRAME_H

#include "stdafx.h"

#include <wx\wx.h>

#include "Struct.h"

#include "DisplayPatternHandler.h"
#include "DisplayPatternWindow.h"

class CircusSimulationFrame : public wxFrame
{

private:

	DisplayPatternHandler pattern_handler;

	DisplayPatternWindow * window_1;
	DisplayPatternWindow * window_2;

	void OnHello(wxCommandEvent &);
	void OnExit(wxCommandEvent &);
	void OnAbout(wxCommandEvent &);

	void Reset(wxCommandEvent &);

	void PopulateFromSingleJugglerPatternsWindow(wxCommandEvent& event);

	void Resize_Internal();
	void Resize(wxSizeEvent &);

	wxDECLARE_EVENT_TABLE();

public:

	CircusSimulationFrame(const wxString &, const wxPoint &, const wxSize &);

	virtual ~CircusSimulationFrame();

};


#endif
