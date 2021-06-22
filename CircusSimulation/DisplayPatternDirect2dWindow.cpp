#include "DisplayPatternDirect2dWindow.h"
#include "Direct2dFactory.h"



wxBEGIN_EVENT_TABLE(DisplayPatternDirect2dWindow, DisplayPatternWindow)

EVT_SIZE(DisplayPatternDirect2dWindow::OnScreenResize)
EVT_PAINT(DisplayPatternDirect2dWindow::OnScreenPaint)

wxEND_EVENT_TABLE()



void DisplayPatternDirect2dWindow::OnScreenPaint(wxPaintEvent& e)
{
	OnScreenPaintD1(*renderTarget);
}



void DisplayPatternDirect2dWindow::OnScreenResize(wxSizeEvent& e)
{
	const wxSize size = GetClientSize();
	renderTarget->Resize(D2D1::SizeU(size.GetWidth(), size.GetHeight()));

	OnScreenResizeD1();
}


DisplayPatternDirect2dWindow::DisplayPatternDirect2dWindow(wxWindow* parent)
	: DisplayPatternWindow(parent),
	renderTarget(NULL)
{
	const wxSize size = GetClientSize();

	Direct2dFactory::GetDrawingFactory()->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			(HWND)GetHandle(),
			D2D1::SizeU(size.GetWidth(), size.GetHeight())
		),
		&renderTarget
	);
}



DisplayPatternDirect2dWindow::~DisplayPatternDirect2dWindow()
{
	renderTarget->Release();
}



ID2D1HwndRenderTarget& DisplayPatternDirect2dWindow::GetRenderTarget()
{
	return *renderTarget;
}