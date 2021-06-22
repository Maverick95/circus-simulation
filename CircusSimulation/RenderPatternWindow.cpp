#include "RenderPatternWindow.h"



wxAutoBufferedPaintDC* ContextPatternWindow<wxAutoBufferedPaintDC>::GetContext()
{
	return (new wxAutoBufferedPaintDC(this));
}

ContextPatternWindow<wxAutoBufferedPaintDC>::ContextPatternWindow(wxWindow* parent)
	: RenderPatternWindow(parent)
{

}

ContextPatternWindow<wxAutoBufferedPaintDC>::~ContextPatternWindow()
{

}




ID2D1HwndRenderTarget* ContextPatternWindow<ID2D1HwndRenderTarget>::GetContext()
{
	return renderTarget;
}

void ContextPatternWindow<ID2D1HwndRenderTarget>::OnScreenResizeD1()
{
	const wxSize size = GetClientSize();
	renderTarget->Resize(D2D1::SizeU(size.GetWidth(), size.GetHeight()));
	OnScreenResizeD2();
}

ContextPatternWindow<ID2D1HwndRenderTarget>::ContextPatternWindow(wxWindow* parent)
	: RenderPatternWindow(parent),
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

ContextPatternWindow<ID2D1HwndRenderTarget>::~ContextPatternWindow()
{
	renderTarget->Release();
}
