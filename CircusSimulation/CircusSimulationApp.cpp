#include "CircusSimulationFrame.h"
#include "CircusSimulationApp.h"

#include "Direct2dFactory.h"



bool CircusSimulationApp::OnInit()
{
	CircusSimulationFrame * frame = new CircusSimulationFrame("Circus Simulation", wxPoint(50, 50), wxSize(450, 340));
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
	Direct2dFactory::Setup();
}

CircusSimulationApp::~CircusSimulationApp()
{
	Direct2dFactory::Teardown();
}