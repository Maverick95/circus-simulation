#include "CircusSimulationFrame.h"
#include "CircusSimulationApp.h"



bool CircusSimulationApp::OnInit()
{
	CircusSimulationFrame * frame = new CircusSimulationFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);

	return true;
}

int CircusSimulationApp::OnExit()
{
	return wxAppConsole::OnExit();
}

CircusSimulationApp::CircusSimulationApp()
	: wxApp()
{
	wxImage::AddHandler(new wxPNGHandler);
}