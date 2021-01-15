#include "stdafx.h"

bool CircusSimulationApp::OnInit()
{
	GraphDataProcessing::Initialize();

	CircusSimulationFrame * frame = new CircusSimulationFrame("Hello World", wxPoint(50, 50), wxSize(450, 340));
	frame->Show(true);

	return true;
}

int CircusSimulationApp::OnExit()
{
	GraphDataProcessing::Shutdown();

	return wxAppConsole::OnExit();
}

CircusSimulationApp::CircusSimulationApp()
	: wxApp()
{
	wxImage::AddHandler(new wxPNGHandler);
}