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

	// Placeholder function for now - this will be replaced later.

	SiteswapPattern* GetRandomPattern();

	unsigned int num_balls;
	unsigned int num_throws;

	void UpdateNumberBalls(wxSpinEvent &);
	void UpdateNumberThrows(wxSpinEvent &);

	void Reset(wxCommandEvent &);
	void Populate(wxCommandEvent &);

	void Resize_Internal();
	void Resize(wxSizeEvent &);

	wxDECLARE_EVENT_TABLE();

public:

	CircusSimulationFrame(const wxString &, const wxPoint &, const wxSize &);

	virtual ~CircusSimulationFrame();

};


#endif
