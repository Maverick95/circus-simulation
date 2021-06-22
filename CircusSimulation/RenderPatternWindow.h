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

	virtual T* GetContext() = 0;
	virtual void OnScreenPaintD1(T* context) = 0;
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
	T* context = GetContext();
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

	virtual wxAutoBufferedPaintDC* GetContext();

public:

	ContextPatternWindow(wxWindow* parent);
	virtual ~ContextPatternWindow();

};



template<>
class ContextPatternWindow<ID2D1HwndRenderTarget> : public RenderPatternWindow<ID2D1HwndRenderTarget>
{

private:

	ID2D1HwndRenderTarget* renderTarget;

protected:

	virtual ID2D1HwndRenderTarget* GetContext();
	virtual void OnScreenResizeD1();
	virtual void OnScreenResizeD2() = 0;

public:

	ContextPatternWindow(wxWindow*);
	virtual ~ContextPatternWindow();

};



#endif
