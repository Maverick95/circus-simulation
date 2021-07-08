#include "RenderPatternWindow.h"



wxWindow* ContextPatternWindow<wxWindow>::GetContext_RenderPattern()
{
	return this;
}

ContextPatternWindow<wxWindow>::ContextPatternWindow(wxWindow* parent)
	: RenderPatternWindow(parent)
{

}

ContextPatternWindow<wxWindow>::~ContextPatternWindow()
{

}




ID2D1HwndRenderTarget* ContextPatternWindow<ID2D1HwndRenderTarget>::GetContext_RenderPattern()
{
	return renderTarget;
}

void ContextPatternWindow<ID2D1HwndRenderTarget>::OnScreenResize_RenderPattern()
{
	const wxSize size = GetClientSize();
	renderTarget->Resize(D2D1::SizeU(size.GetWidth(), size.GetHeight()));
	OnScreenResize_ContextPattern();
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
