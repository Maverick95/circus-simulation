#ifndef DISPLAY_JUGGLING_WINDOW_H
#define DISPLAY_JUGGLING_WINDOW_H

#include <wx\wx.h>

#include "Macro.h"
#include "stdafx.h"
#include "Functions.h"
#include "RenderPatternWindow.h"
#include "SettingsEvents.h"



/* ### DECLARE ### */



template <class T>
class DisplayJugglingWindow : public ContextPatternWindow<T>
{

private:

	bool num_sites_fixed;

	unsigned int num_sites;
	unsigned int num_actions;
	unsigned int num_balls;

	unsigned int* * balls_site_source;
	unsigned int* * balls_site_destination;

	unsigned int mapping_length;

	unsigned int* indices_sites;

	unsigned int* ** mapping_site_source;
	unsigned int* ** mapping_site_destination;

	unsigned int mapping_current_factor;

	void SetNumberSites(const SettingsEvents::SetNumberSitesEvent& event);

protected:

	virtual void OnBallsUpdate_DisplayPattern();
	virtual void Reset_DisplayPattern();
	virtual void Populate_DisplayPattern();
	virtual void Stop_DisplayPattern();

	virtual void Reset_DisplayJuggling() = 0;
	virtual void Populate_DisplayJuggling() = 0;
	virtual void SetNumberSites_DisplayJuggling() = 0;
	
	virtual DisplayPatternHandler * GetValidHandler() override;

	// Internal accessor functions.

	unsigned int GetNumberSites() const;

	unsigned int * GetBallSiteSource(const unsigned int &);
	unsigned int * GetBallSiteDestination(const unsigned int &);

public:

	DisplayJugglingWindow(wxWindow * parent, const unsigned int& numberSites, const bool& isNumberSitesFixed);

	virtual ~DisplayJugglingWindow();

	wxDECLARE_EVENT_TABLE();

};



/* ### DEFINE ### */



wxBEGIN_EVENT_TABLE_INHERITED_TEMPLATE1(DisplayJugglingWindow, ContextPatternWindow, T1)

EVT_SET_NUMBER_SITES(DisplayJugglingWindow<T1>::SetNumberSites)

wxEND_EVENT_TABLE()



template<class T>
void DisplayJugglingWindow<T>::SetNumberSites(const SettingsEvents::SetNumberSitesEvent& event)
{
	if (!num_sites_fixed && num_sites != event.NumberSites())
	{
		num_sites = event.NumberSites();
		
		delete[] indices_sites;
		indices_sites = new unsigned int[num_sites];
		for (unsigned int i = 0U; i < num_sites; i++)
		{
			indices_sites[i] = i;
		}

		auto h = GetValidHandler();

		if (h != NULL)
		{
			// Reset

			for (unsigned int i = 0; i < mapping_length; i++)
			{
				delete[] mapping_site_source[i];
				delete[] mapping_site_destination[i];
			}

			delete[] mapping_site_source;
			delete[] mapping_site_destination;

			for (unsigned int i = 0U; i < num_balls; i++)
			{
				balls_site_source[i] = NULL;
				balls_site_destination[i] = NULL;
			}

			mapping_length = 0;
			mapping_current_factor = 0;

			// Recalculate

			/* See large comment in Populate for full description. */

			unsigned int balls_mapping_length = h->GetDisplayPattern()->GetTotalLength();

			unsigned int* lcm_data_1 = new unsigned int[2];
			lcm_data_1[0] = num_actions;
			lcm_data_1[1] = num_sites;
			unsigned int lcm_result_1 = Functions::LowestCommonMultiple(lcm_data_1, 2);
			delete[] lcm_data_1;

			unsigned int* lcm_data_2 = new unsigned int[2];
			lcm_data_2[0] = lcm_result_1 / num_actions;
			lcm_data_2[1] = balls_mapping_length;
			unsigned int lcm_result_2 = Functions::LowestCommonMultiple(lcm_data_2, 2);
			delete[] lcm_data_2;

			mapping_length = lcm_result_2;

			mapping_site_source = new unsigned int** [mapping_length];
			mapping_site_destination = new unsigned int** [mapping_length];

			for (unsigned int i = 0; i < mapping_length; i++)
			{
				mapping_site_source[i] = new unsigned int* [num_actions];
				mapping_site_destination[i] = new unsigned int* [num_actions];

				for (unsigned int j = 0; j < num_actions; j++)
				{
					mapping_site_source[i][j] = NULL;
					mapping_site_destination[i][j] = NULL;
				}
			}

			// Set up the source sites (cyclical).

			unsigned int site_index = 0;

			for (unsigned int i = 0; i < mapping_length; i++)
			{
				for (unsigned int j = 0; j < num_actions; j++)
				{
					if (h->GetDisplayPattern()->GetBall(i % balls_mapping_length, j) != NULL)
					{
						mapping_site_source[i][j] = &(indices_sites[site_index]);
					}

					site_index++;
					if (site_index == num_sites) { site_index = 0; }
				}
			}

			// Set up the destination sites.

			for (unsigned int i = 0; i < mapping_length; i++)
			{
				for (unsigned int j = 0; j < num_actions; j++)
				{
					if (mapping_site_source[i][j] != NULL)
					{
						unsigned int current_throw = *(h->GetDisplayPattern()->GetThrow(i % balls_mapping_length, j));
						unsigned int current_action_index = *(h->GetDisplayPattern()->GetAction(i % balls_mapping_length, j));

						unsigned int destination_index = (i + current_throw) % mapping_length;

						mapping_site_destination[i][j] = mapping_site_source[destination_index][current_action_index];
					}
				}
			}

			// Potentially may need to copy in ball mappings here, maybe not.

		}

		SetNumberSites_DisplayJuggling();
	}
}



template<class T>
unsigned int DisplayJugglingWindow<T>::GetNumberSites() const
{
	return num_sites;
}



template <class T>
void DisplayJugglingWindow<T>::Reset_DisplayPattern()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		for (unsigned int i = 0; i < mapping_length; i++)
		{
			delete[] mapping_site_source[i];
			delete[] mapping_site_destination[i];
		}

		delete[] mapping_site_source;
		delete[] mapping_site_destination;

		delete[] balls_site_source;
		delete[] balls_site_destination;
	}

	num_actions = 0;
	num_balls = 0;
	mapping_length = 0;

	mapping_site_source = NULL;
	mapping_site_destination = NULL;
	balls_site_source = NULL;
	balls_site_destination = NULL;

	mapping_current_factor = 0;

	Reset_DisplayJuggling();
}



template <class T>
void DisplayJugglingWindow<T>::Populate_DisplayPattern()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		mapping_current_factor = 0;

		// Set up information for ball source/destination sites.

		num_balls = h->GetDisplayPattern()->GetNumberBalls();

		balls_site_source = new unsigned int* [num_balls];
		balls_site_destination = new unsigned int* [num_balls];

		for (unsigned int i = 0; i < num_balls; i++)
		{
			balls_site_source[i] = NULL;
			balls_site_destination[i] = NULL;
		}

		/*
		
		Calculate mapping_length, the total "beat" length of the repetitive pattern.
		
		This is based on -
		a) number of sites,
		b) number of actions,
		c) method of cycling through the sites,
		d) the pattern.

		By default, sites are cycled through in a linear fashion.
		e.g. 5 sites and 2 actions, the choice of sites would be -
		[1 2] [3 4] [5 1] [2 3] [4 5] [1 2] ...

		lcm_result_1 = how many sites are cycled through until the site/action pattern repeats

		However this is the number of sites
		lcm_result_1 / num_actions is the "beat" length until the site/action pattern repeats

		balls_mapping_length = "beat" length of the pattern just mapping balls to actions

		Therefore -

		mapping_length = LCM(lcm_result_1, balls_mapping_length)

		*/
		
		num_actions = h->GetDisplayPattern()->GetNumberActions();

		unsigned int balls_mapping_length = h->GetDisplayPattern()->GetTotalLength();

		unsigned int* lcm_data_1 = new unsigned int[2];
		lcm_data_1[0] = num_actions;
		lcm_data_1[1] = num_sites;
		unsigned int lcm_result_1 = Functions::LowestCommonMultiple(lcm_data_1, 2);
		delete[] lcm_data_1;

		unsigned int* lcm_data_2 = new unsigned int[2];
		lcm_data_2[0] = lcm_result_1 / num_actions;
		lcm_data_2[1] = balls_mapping_length;
		unsigned int lcm_result_2 = Functions::LowestCommonMultiple(lcm_data_2, 2);
		delete[] lcm_data_2;

		mapping_length = lcm_result_2;

		mapping_site_source = new unsigned int** [mapping_length];
		mapping_site_destination = new unsigned int** [mapping_length];

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			mapping_site_source[i] = new unsigned int* [num_actions];
			mapping_site_destination[i] = new unsigned int* [num_actions];

			for (unsigned int j = 0; j < num_actions; j++)
			{
				mapping_site_source[i][j] = NULL;
				mapping_site_destination[i][j] = NULL;
			}
		}

		// Set up the source sites (cyclical).

		unsigned int site_index = 0;

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			for (unsigned int j = 0; j < num_actions; j++)
			{
				if (h->GetDisplayPattern()->GetBall(i % balls_mapping_length, j) != NULL)
				{
					mapping_site_source[i][j] = &(indices_sites[site_index]);
				}

				site_index++;
				if (site_index == num_sites) { site_index = 0; }
			}
		}

		// Set up the destination sites.

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			for (unsigned int j = 0; j < num_actions; j++)
			{
				if (mapping_site_source[i][j] != NULL)
				{
					unsigned int current_throw = *(h->GetDisplayPattern()->GetThrow(i % balls_mapping_length, j));
					unsigned int current_action_index = *(h->GetDisplayPattern()->GetAction(i % balls_mapping_length, j));

					unsigned int destination_index = (i + current_throw) % mapping_length;

					mapping_site_destination[i][j] = mapping_site_source[destination_index][current_action_index];
				}
			}
		}
	}

	Populate_DisplayJuggling();
}



template<class T>
void DisplayJugglingWindow<T>::Stop_DisplayPattern()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		mapping_current_factor = 0;
	}

	Refresh(false, NULL);
}



template <class T>
DisplayPatternHandler* DisplayJugglingWindow<T>::GetValidHandler()
{
	DisplayPatternHandler* return_value = NULL;

	auto h = DisplayPatternWindow::GetValidHandler();

	if (h != NULL)
	{
		if (h->GetDisplayPattern()->GetNumberActions() <= num_sites)
		{
			return_value = h;
		}
	}

	return return_value;
}



template <class T>
unsigned int* DisplayJugglingWindow<T>::GetBallSiteSource(const unsigned int& i)
{
	unsigned int* return_value = NULL;

	auto h = GetValidHandler();

	if (h != NULL)
	{
		if (i < num_balls)
		{
			return_value = balls_site_source[i];
		}
	}

	return return_value;
}



template <class T>
unsigned int* DisplayJugglingWindow<T>::GetBallSiteDestination(const unsigned int& i)
{
	unsigned int* return_value = NULL;

	auto h = GetValidHandler();

	if (h != NULL)
	{
		if (i < num_balls)
		{
			return_value = balls_site_destination[i];
		}
	}

	return return_value;
}



template <class T>
void DisplayJugglingWindow<T>::OnBallsUpdate_DisplayPattern()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		unsigned int handler_mapping_current = h->GetMappingCurrent();
		unsigned int handler_total_length = h->GetDisplayPattern()->GetTotalLength();

		unsigned int display_mapping_current = (mapping_current_factor * handler_total_length) + handler_mapping_current;

		for (unsigned int i = 0; i < num_actions; i++)
		{
			const unsigned int* ball_current = h->GetDisplayPattern()->GetBall(handler_mapping_current, i);

			if (ball_current != NULL)
			{
				balls_site_source[*ball_current] = mapping_site_source[display_mapping_current][i];
				balls_site_destination[*ball_current] = mapping_site_destination[display_mapping_current][i];
			}
		}

		// Update factor indices if necessary.

		if (handler_mapping_current == (handler_total_length - 1)) { mapping_current_factor++; }
		if (mapping_current_factor * handler_total_length == mapping_length) { mapping_current_factor = 0; }
	}
}



template<class T>
DisplayJugglingWindow<T>::DisplayJugglingWindow(wxWindow* parent, const unsigned int& numberSites, const bool& isNumberSitesFixed)
	: ContextPatternWindow(parent),
	num_sites_fixed(isNumberSitesFixed),
	num_sites(numberSites == 0 ? 1 : numberSites),
	num_actions(0),
	num_balls(0),
	balls_site_source(NULL),
	balls_site_destination(NULL),
	mapping_length(0),
	indices_sites(NULL),
	mapping_site_source(NULL),
	mapping_site_destination(NULL),
	mapping_current_factor(0)
{
	indices_sites = new unsigned int[num_sites];

	for (unsigned int i = 0; i < num_sites; i++)
	{
		indices_sites[i] = i;
	}
}



template <class T>
DisplayJugglingWindow<T>::~DisplayJugglingWindow()
{
	delete[] indices_sites;

	auto h = GetValidHandler();

	if (h != NULL)
	{
		for (unsigned int i = 0; i < mapping_length; i++)
		{
			delete[] mapping_site_source[i];
			delete[] mapping_site_destination[i];
		}

		delete[] mapping_site_source;
		delete[] mapping_site_destination;

		delete[] balls_site_source;
		delete[] balls_site_destination;
	}
}



#endif
