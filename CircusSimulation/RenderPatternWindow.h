#ifndef RENDER_PATTERN_WINDOW_H
#define RENDER_PATTERN_WINDOW_H

#include "DisplayPatternWindow.h"
#include "d2d1.h"
#include "Direct2dFactory.h"



/* ### DECLARE ### */



template <class T>
class RenderPatternWindow : public DisplayPatternWindow
{

private:

	void OnScreenResize(wxSizeEvent& e);
	void OnScreenPaint(wxPaintEvent& e);

protected:

	virtual T& GetContext() = 0;
	virtual void OnScreenPaintD1(T& context) = 0;
	virtual void OnScreenResizeD1() = 0;

public:

	RenderPatternWindow(wxWindow* parent);
	virtual ~RenderPatternWindow();

};



/* ### DEFINE ### */



template <class T>
void RenderPatternWindow<T>::OnScreenResize(wxSizeEvent& e)
{
	OnScreenResizeD1();
}



template <class T>
void RenderPatternWindow<T>::OnScreenPaint(wxPaintEvent& e)
{
	T& context = GetContext();
	OnScreenPaintD1(context);
}



template <class T>
RenderPatternWindow<T>::RenderPatternWindow(wxWindow* parent)
	: DisplayPatternWindow(parent)
{
	this->Bind(wxEVT_PAINT, &RenderPatternWindow<T>::OnScreenPaint, this);
	this->Bind(wxEVT_SIZE, &RenderPatternWindow<T>::OnScreenResize, this);
}



template <class T>
RenderPatternWindow<T>::~RenderPatternWindow<T>()
{

}



/* ### LEVEL 2 ### */



template<class T>
class ContextPatternWindow : public RenderPatternWindow<T>
{

public:

};



template<>
class ContextPatternWindow<wxAutoBufferedPaintDC> : public RenderPatternWindow<wxAutoBufferedPaintDC>
{

protected:

	virtual wxAutoBufferedPaintDC& GetContext();

public:

	ContextPatternWindow(wxWindow* parent);
	virtual ~ContextPatternWindow();

};

wxAutoBufferedPaintDC& ContextPatternWindow<wxAutoBufferedPaintDC>::GetContext()
{
	return wxAutoBufferedPaintDC(this);
}

ContextPatternWindow<wxAutoBufferedPaintDC>::ContextPatternWindow(wxWindow* parent)
	: RenderPatternWindow(parent)
{

}

ContextPatternWindow<wxAutoBufferedPaintDC>::~ContextPatternWindow()
{

}



template<>
class ContextPatternWindow<ID2D1HwndRenderTarget> : public RenderPatternWindow<ID2D1HwndRenderTarget>
{

private:

	ID2D1HwndRenderTarget* renderTarget;

protected:

	virtual ID2D1HwndRenderTarget& GetContext();

public:

	ContextPatternWindow(wxWindow*);
	virtual ~ContextPatternWindow();

};

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

ID2D1HwndRenderTarget& ContextPatternWindow<ID2D1HwndRenderTarget>::GetContext()
{
	return *renderTarget;
}






#endif
