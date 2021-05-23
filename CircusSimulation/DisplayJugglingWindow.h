#ifndef DISPLAY_JUGGLING_WINDOW_H
#define DISPLAY_JUGGLING_WINDOW_H

#include "stdafx.h"

#include "DisplayPatternDirect2dWindow.h"

class DisplayJugglingWindow : public DisplayPatternDirect2dWindow
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

	virtual void OnBallsUpdate();

	virtual void ResetD1();
	virtual void PopulateD1();
	virtual void StopD1();

	virtual void OnBallsUpdateD1() = 0;

	virtual void ResetD2() = 0;
	virtual void PopulateD2() = 0;
	
	virtual DisplayPatternHandler * GetValidHandler() override;

	// Internal accessor functions.

	unsigned int * GetBallSiteSource(const unsigned int &);
	unsigned int * GetBallSiteDestination(const unsigned int &);

public:

	DisplayJugglingWindow(wxWindow *, const unsigned int &);

	virtual ~DisplayJugglingWindow();

};



#endif
