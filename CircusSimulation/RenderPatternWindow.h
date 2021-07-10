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

	virtual T* GetContext_RenderPattern() = 0;
	virtual void OnScreenPaint_RenderPattern(T* context) = 0;
	virtual void OnScreenResize_RenderPattern() = 0;

public:

	RenderPatternWindow(wxWindow* parent);
	virtual ~RenderPatternWindow();

};



/* ### DEFINE ### */



template <class T>
void RenderPatternWindow<T>::OnScreenResize(wxSizeEvent& e)
{
	OnScreenResize_RenderPattern();
	Refresh(false, NULL);
}

template <class T>
void RenderPatternWindow<T>::OnScreenPaint(wxPaintEvent& e)
{
	T* context = GetContext_RenderPattern();
	OnScreenPaint_RenderPattern(context);
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

	wxWindow* GetContext_RenderPattern();

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

	ID2D1HwndRenderTarget* GetContext_RenderPattern();
	void OnScreenResize_RenderPattern();
	virtual void OnScreenResize_ContextPattern() = 0;

public:

	ContextPatternWindow(wxWindow*);
	virtual ~ContextPatternWindow();

};



#endif
