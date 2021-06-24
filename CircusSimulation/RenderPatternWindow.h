#ifndef RENDER_PATTERN_WINDOW_H
#define RENDER_PATTERN_WINDOW_H

#include "DisplayPatternWindow.h"
#include "d2d1.h"
#include "Direct2dFactory.h"



/* ### LEVEL 1 ### */



/* ### DECLARE ### */



template <class T>
class RenderPatternWindow : public DisplayPatternWindow
{

private:

	void OnScreenResize(wxSizeEvent& e);
	void OnScreenPaint(wxPaintEvent& e);

protected:

	virtual T* GetContext() = 0;
	virtual void OnScreenPaint(T* context) = 0;
	virtual void OnScreenResize() = 0;

public:

	RenderPatternWindow(wxWindow* parent);
	virtual ~RenderPatternWindow();

};



/* ### DEFINE ### */



template <class T>
void RenderPatternWindow<T>::OnScreenResize(wxSizeEvent& e)
{
	OnScreenResize();
}

template <class T>
void RenderPatternWindow<T>::OnScreenPaint(wxPaintEvent& e)
{
	T* context = GetContext();
	OnScreenPaint(context);
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



/* ### DECLARE ### */



template<class T>
class ContextPatternWindow : public RenderPatternWindow<T>
{ };

template<>
class ContextPatternWindow<wxWindow> : public RenderPatternWindow<wxWindow>
{

protected:

	wxWindow* GetContext();

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

	ID2D1HwndRenderTarget* GetContext();
	void OnScreenResize();
	virtual void OnScreenResizeD2() = 0;

public:

	ContextPatternWindow(wxWindow*);
	virtual ~ContextPatternWindow();

};



#endif
