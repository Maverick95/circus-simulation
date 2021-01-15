#ifndef DISPLAY_JUGGLING_WINDOW_H
#define DISPLAY_JUGGLING_WINDOW_H



class DisplayJugglingWindow : public DisplayPatternWindow
{

private:

	unsigned int num_sites;
	unsigned int num_actions;
	unsigned int num_balls;

	unsigned int * * balls_site_source;
	unsigned int * * balls_site_destination;

	unsigned int mapping_length;

	unsigned int * indices_sites;

	unsigned int ** * mapping_site_source;
	unsigned int ** * mapping_site_destination;

	unsigned int mapping_current_factor;

protected:

	virtual void Reset_Derived();
	virtual void Populate_Derived();

	virtual void Stop_Derived();

	virtual void Reset_Derived_2() = 0;
	virtual void Populate_Derived_2() = 0;
	virtual void OnBallsUpdate_Derived_2() = 0;

	virtual DisplayPatternHandler * GetValidHandler() override;

	// Internal accessor functions.

	unsigned int * GetBallSiteSource(const unsigned int &);
	unsigned int * GetBallSiteDestination(const unsigned int &);

public:

	DisplayJugglingWindow(wxWindow *, const unsigned int &);

	virtual ~DisplayJugglingWindow();

	virtual void OnBallsUpdate_Derived();

};



#endif
