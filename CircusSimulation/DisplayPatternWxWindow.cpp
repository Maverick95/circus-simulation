#include "DisplayPatternWxWindow.h"



wxBEGIN_EVENT_TABLE(DisplayPatternWxWindow, DisplayPatternWindow)

EVT_PAINT(DisplayPatternWxWindow::OnScreenPaint)

wxEND_EVENT_TABLE()



void DisplayPatternWxWindow::OnScreenPaint(wxPaintEvent& e)
{
	wxAutoBufferedPaintDC dc(this);

	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();

	auto h = GetValidHandler();

	if (h != NULL)
	{
		// Apply any derived additional functionality.

		OnScreenPaintD1(dc);
	}
}



DisplayPatternWxWindow::DisplayPatternWxWindow(wxWindow* parent) :
	DisplayPatternWindow(parent)
{

}



DisplayPatternWxWindow::~DisplayPatternWxWindow()
{

}