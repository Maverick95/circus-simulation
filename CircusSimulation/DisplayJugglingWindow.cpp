#include "DisplayPatternHandler.h"
#include "Functions.h"

#include "DisplayJugglingWindow.h"



void DisplayJugglingWindow::Reset_Derived()
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

	Reset_Derived_2();
}



void DisplayJugglingWindow::Populate_Derived()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		mapping_current_factor = 0;

		// Set up information for ball source/destination sites.

		num_balls = h->GetDisplayPattern()->GetNumberBalls();

		balls_site_source = new unsigned int*[num_balls];
		balls_site_destination = new unsigned int*[num_balls];

		for (unsigned int i = 0; i < num_balls; i++)
		{
			balls_site_source[i] = NULL;
			balls_site_destination[i] = NULL;
		}

		// Use data to obtain and set mapping_length, initialize arrays.

		num_actions = h->GetDisplayPattern()->GetNumberActions();
		
		unsigned int balls_mapping_length = h->GetDisplayPattern()->GetTotalLength();
		
		unsigned int * lcm_data_1 = new unsigned int[2];
		lcm_data_1[0] = num_actions;
		lcm_data_1[1] = num_sites;
		unsigned int lcm_result_1 = Functions::LowestCommonMultiple(lcm_data_1, 2);
		delete[] lcm_data_1;

		unsigned int * lcm_data_2 = new unsigned int[2];
		lcm_data_2[0] = lcm_result_1 / num_actions;
		lcm_data_2[1] = balls_mapping_length;
		unsigned int lcm_result_2 = Functions::LowestCommonMultiple(lcm_data_2, 2);
		delete[] lcm_data_2;

		mapping_length = lcm_result_2;

		mapping_site_source = new unsigned int**[mapping_length];
		mapping_site_destination = new unsigned int**[mapping_length];

		for (unsigned int i = 0; i < mapping_length; i++)
		{
			mapping_site_source[i] = new unsigned int*[num_actions];
			mapping_site_destination[i] = new unsigned int*[num_actions];

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
	
	Populate_Derived_2();
}

void DisplayJugglingWindow::Stop_Derived()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		mapping_current_factor = 0;
	}

	Refresh(false, NULL);
}

DisplayPatternHandler * DisplayJugglingWindow::GetValidHandler()
{
	DisplayPatternHandler * return_value = NULL;

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


unsigned int * DisplayJugglingWindow::GetBallSiteSource(const unsigned int & i)
{
	unsigned int * return_value = NULL;

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



unsigned int * DisplayJugglingWindow::GetBallSiteDestination(const unsigned int & i)
{
	unsigned int * return_value = NULL;

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



void DisplayJugglingWindow::OnBallsUpdate_Derived()
{
	auto h = GetValidHandler();

	if (h != NULL)
	{
		unsigned int handler_mapping_current = h->GetMappingCurrent();
		unsigned int handler_total_length = h->GetDisplayPattern()->GetTotalLength();

		unsigned int display_mapping_current = (mapping_current_factor * handler_total_length) + handler_mapping_current;

		for (unsigned int i = 0; i < num_actions; i++)
		{
			const unsigned int * ball_current = h->GetDisplayPattern()->GetBall(handler_mapping_current, i);
			
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

	OnBallsUpdate_Derived_2();
}



DisplayJugglingWindow::DisplayJugglingWindow(wxWindow * parent, const unsigned int & ns)
	: DisplayPatternWindow(parent),
	num_sites(ns == 0 ? 1 : ns),
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



DisplayJugglingWindow::~DisplayJugglingWindow()
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

