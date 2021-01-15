#ifndef STDAFWX_H
#define STDAFWX_H



class TestBallDrawingWindow : public DisplayJugglingWindow
{

private:

	double dwell_ratio;

	double * plot_x;
	double * plot_y;

	double * window_ratios_x;
	double * window_ratios_y;

	unsigned int * window_widths_x;
	unsigned int * window_widths_y;

	void OnScreenResize_Internal();
	void OnScreenResize(wxSizeEvent &);

	wxDECLARE_EVENT_TABLE();

protected:

	virtual void OnScreenUpdate_Derived(const long &);
	virtual void OnScreenPaint_Derived(wxAutoBufferedPaintDC &);

	virtual void Reset_Derived_2();
	virtual void Populate_Derived_2();
	virtual void OnBallsUpdate_Derived_2();

public:

	TestBallDrawingWindow(wxWindow * parent, const unsigned int * w_r_x = NULL, const unsigned int * w_r_y = NULL, const double & dr = 1.0);

	virtual ~TestBallDrawingWindow();

};


#endif
