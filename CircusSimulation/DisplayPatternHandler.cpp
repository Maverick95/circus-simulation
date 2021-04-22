#include "Settings.h"

#include "DisplayPatternHandler.h"

#include "DisplayPatternWindow.h"


static const int TIMER_BALLS_UPDATE = 2;

static const int BUTTON_PLAY = 1;
static const int BUTTON_STOP = 2;
static const int BUTTON_PAUSE = 3;
static const int BUTTON_PLAY_ONCE_FORWARD = 4;
static const int BUTTON_SPEED_CHANGE_HALF = 5;
static const int BUTTON_SPEED_CHANGE_NORMAL = 6;
static const int BUTTON_SPEED_CHANGE_DOUBLE = 7;



wxBEGIN_EVENT_TABLE(DisplayPatternHandler, wxEvtHandler)

EVT_TIMER(TIMER_BALLS_UPDATE, DisplayPatternHandler::OnBallsUpdate)
EVT_BUTTON(BUTTON_PLAY, DisplayPatternHandler::Play)
EVT_BUTTON(BUTTON_STOP, DisplayPatternHandler::Stop)
EVT_BUTTON(BUTTON_PAUSE, DisplayPatternHandler::Pause)
EVT_BUTTON(BUTTON_PLAY_ONCE_FORWARD, DisplayPatternHandler::PlayOnce_Forward)
EVT_BUTTON(BUTTON_SPEED_CHANGE_HALF, DisplayPatternHandler::SpeedChange_Half)
EVT_BUTTON(BUTTON_SPEED_CHANGE_NORMAL, DisplayPatternHandler::SpeedChange_Normal)
EVT_BUTTON(BUTTON_SPEED_CHANGE_DOUBLE, DisplayPatternHandler::SpeedChange_Double)

wxEND_EVENT_TABLE()



void DisplayPatternHandler::StartTimers()
{
	timer_update_balls->Start(pattern_beat_time_milliseconds);
	stopwatch_update_balls->Start();
}

void DisplayPatternHandler::StopTimers()
{
	timer_update_balls->Stop();
	stopwatch_update_balls->Pause();
}

void DisplayPatternHandler::Calculate_PatternBeatTime_Milliseconds()
{
	double speed_factor = 1.0;

	switch (speed)
	{
	case SPD_HALF: speed_factor = 2.0; break;
	case SPD_DOUBLE: speed_factor = 0.5; break;
	}

	long pbtm = (long)(speed_factor * Settings::Pattern_BeatTime_Milliseconds());

	if (pbtm == 0L) { pbtm = 1L; }

	pattern_beat_time_milliseconds = pbtm;
}


void DisplayPatternHandler::OnBallsUpdate_CheckPause()
{
	if (is_valid)
	{
		// Check and apply pause functionality if required.

		switch (state)
		{
		case PH_STATE_PAUSE_TRANSIT:
		case PH_STATE_SINGLE_BEAT_FORWARD:
		{
			if (update_balls_to_pause == 0)
			{
				StopTimers();
				update_balls_to_pause = -1;
				state = PH_STATE_PAUSE;
			}
		}
		break;
		}

		// Apply clean-up if required.

		switch (state)
		{
		case PH_STATE_PAUSE_TRANSIT:
		case PH_STATE_SINGLE_BEAT_FORWARD:
		{
			update_balls_to_pause--;
		}
		break;
		}
	}
}

void DisplayPatternHandler::OnBallsUpdate_ProcessNextActions()
{
	if (is_valid)
	{
		// Apply standard functionality if required.

		switch (state)
		{
		case PH_STATE_PLAY:
		case PH_STATE_PAUSE_TRANSIT:
		case PH_STATE_SINGLE_BEAT_FORWARD:
		{
			// Increase beats elapsed for each ball.

			for (unsigned int i = 0; i < num_balls; i++)
			{
				data_balls[i].IncreaseBeatsElapsed();
			}

			// Assign the next throw(s) to the correct ball(s) (if required).

			unsigned int num_actions = display_pattern->GetNumberActions();

			for (unsigned int i = 0; i < num_actions; i++)
			{
				if (display_pattern->GetBall(mapping_current, i) != NULL)
				{
					unsigned int index_ball = *(display_pattern->GetBall(mapping_current, i));
					unsigned int index_action = *(display_pattern->GetAction(mapping_current, i));

					data_balls[index_ball].AssignNewThrow(*(display_pattern->GetThrow(mapping_current, i)), index_action);
				}
			}

			// Loop through related windows and apply additional functionality / redraw.

			for (auto i = windows.begin(); i != windows.end(); i++)
			{
				(*i)->OnBallsUpdate();
				(*i)->Update();
			}

			// Update the current mapping index.

			if (mapping_current == (display_pattern->GetTotalLength() - 1)) { mapping_current = 0; }
			else { mapping_current++; }

			// Need to restart the stopwatch.

			stopwatch_update_balls->Start();
		}
		break;
		}
	}
}

void DisplayPatternHandler::OnBallsUpdate_CheckSpeed(bool start_timers = true)
{
	if (is_valid)
	{
		// Apply speed changes if required.

		switch (state)
		{
		case PH_STATE_PLAY:
		case PH_STATE_PAUSE_TRANSIT:
		case PH_STATE_SINGLE_BEAT_FORWARD:
		{
			if (speed_change != SPD_CHG_NONE)
			{
				switch (speed_change)
				{
				case SPD_CHG_HALF: speed = SPD_HALF; break;
				case SPD_CHG_NORMAL: speed = SPD_NORMAL; break;
				case SPD_CHG_DOUBLE: speed = SPD_DOUBLE; break;
				}

				speed_change = SPD_CHG_NONE;

				Calculate_PatternBeatTime_Milliseconds();
				
				if (start_timers) { StartTimers(); }
			}
		}
		break;
		}
	}
}


void DisplayPatternHandler::OnBallsUpdate(wxTimerEvent& event)
{
	OnBallsUpdate_CheckPause();
	OnBallsUpdate_ProcessNextActions();
	OnBallsUpdate_CheckSpeed();
}

DisplayPatternHandler::DisplayPatternHandler(wxWindow * parent)
	: wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0L),
	state(PH_STATE_EMPTY),
	speed(SPD_NORMAL),
	speed_change(SPD_CHG_NONE),
	display_pattern(NULL),
	is_valid(false),
	num_balls(0),
	update_balls_to_pause(-1),
	data_balls(NULL),
	mapping_current(0),
	pattern_beat_time_milliseconds(0L),
	timer_update_balls(NULL),
	stopwatch_update_balls(NULL),
	windows(std::vector<DisplayPatternWindow *>())
{
	// Add button controls.

	wxBoxSizer * sz_button_controls = new wxBoxSizer(wxHORIZONTAL);

	wxButton * bt_play = new wxButton(this, BUTTON_PLAY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	wxButton * bt_stop = new wxButton(this, BUTTON_STOP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	wxButton * bt_pause = new wxButton(this, BUTTON_PAUSE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	wxButton * bt_play_once_forward = new wxButton(this, BUTTON_PLAY_ONCE_FORWARD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	//wxButton * bt_speed_change_half = new wxButton(this, BUTTON_SPEED_CHANGE_HALF, wxString("Half Speed"));
	//wxButton * bt_speed_change_normal = new wxButton(this, BUTTON_SPEED_CHANGE_NORMAL, wxString("Normal Speed"));
	//wxButton * bt_speed_change_double = new wxButton(this, BUTTON_SPEED_CHANGE_DOUBLE, wxString("Double Speed"));
 
	bt_play->SetBitmapLabel(wxBITMAP_PNG(IDB_PLAY_ENABLED));
	bt_play->SetBitmapDisabled(wxBITMAP_PNG(IDB_PLAY_DISABLED));
	bt_play->SetBitmapPressed(wxBITMAP_PNG(IDB_PLAY_PRESSED));

	bt_stop->SetBitmapLabel(wxBITMAP_PNG(IDB_STOP_ENABLED));
	bt_stop->SetBitmapDisabled(wxBITMAP_PNG(IDB_STOP_DISABLED));
	bt_stop->SetBitmapPressed(wxBITMAP_PNG(IDB_STOP_PRESSED));

	bt_pause->SetBitmapLabel(wxBITMAP_PNG(IDB_PAUSE_ENABLED));
	bt_pause->SetBitmapDisabled(wxBITMAP_PNG(IDB_PAUSE_DISABLED));
	bt_pause->SetBitmapPressed(wxBITMAP_PNG(IDB_PAUSE_PRESSED));

	bt_play_once_forward->SetBitmapLabel(wxBITMAP_PNG(IDB_FORWARD_ENABLED));
	bt_play_once_forward->SetBitmapDisabled(wxBITMAP_PNG(IDB_FORWARD_DISABLED));
	bt_play_once_forward->SetBitmapPressed(wxBITMAP_PNG(IDB_FORWARD_PRESSED));
	
	sz_button_controls->Add(bt_play);
	sz_button_controls->Add(bt_stop);
	sz_button_controls->Add(bt_pause);
	sz_button_controls->Add(bt_play_once_forward);
	
	//sz_button_controls->Add(bt_speed_change_half);
	//sz_button_controls->Add(bt_speed_change_normal);
	//sz_button_controls->Add(bt_speed_change_double);
	//sz_button_controls->Add(bt_speed_change_double, 1, wxEXPAND); For reference purposes.

	SetSizer(sz_button_controls);
}

DisplayPatternHandler::~DisplayPatternHandler()
{
	// First you need to reset all the windows linked to the handler and remove their handler link.

	for (auto i = windows.begin(); i != windows.end(); i++)
	{
		(*i)->Reset();
		(*i)->handler = NULL;
	}

	// Then proceed with regular deletion.

	if (display_pattern != NULL)
	{
		delete display_pattern;
	}

	if (is_valid)
	{
		delete[] data_balls;
		delete timer_update_balls;
		delete stopwatch_update_balls;
	}
}

void DisplayPatternHandler::AddWindow(DisplayPatternWindow * w)
{
	if (w != NULL)
	{
		// Window must not already be present.

		bool is_present = false;

		for (auto i = windows.begin(); i != windows.end(); i++)
		{
			if (w == (*i))
			{
				is_present = true;
				break;
			}
		}

		if (!is_present)
		{
			// First the window must be reset.

			w->Reset();

			// Then the window must be removed from it's handler (if relevant).

			if (w->handler != NULL)
			{
				for (auto i = w->handler->windows.begin(); i != w->handler->windows.end(); i++)
				{
					if (w == (*i))
					{
						w->handler->windows.erase(i);
						break;
					}
				}

				w->handler = NULL;
			}

			// Then the window can be linked with this handler.

			w->handler = this;

			// Then the window can be populated.

			w->Populate();

			// And finally added to the list.

			windows.push_back(w);
		}
	}
}

void DisplayPatternHandler::RemoveWindow(DisplayPatternWindow * w)
{
	if (w != NULL)
	{
		// Window must be present in the current list to be removed.

		for (auto i = windows.begin(); i != windows.end(); i++)
		{
			if (w == (*i))
			{
				if (w->full_removal)
				{
					// Window must be reset.
					w->Reset();
					// Handler must be removed.
					w->handler = NULL;
				}

				// And finally removed from the list.

				windows.erase(i);
				break;
			}
		}
	}
}

void DisplayPatternHandler::Reset()
{
	for (auto i = windows.begin(); i != windows.end(); i++)
	{
		(*i)->Reset();
	}

	if (display_pattern != NULL)
	{
		delete display_pattern;
	}

	if (is_valid)
	{
		delete[] data_balls;
		delete timer_update_balls;
		delete stopwatch_update_balls;
	}

	// Note - the only internal variable that doesn't change is the vector of Windows linked to this Handler.

	display_pattern = NULL;
	is_valid = false;
	num_balls = 0;
	update_balls_to_pause = -1;
	data_balls = NULL;
	mapping_current = 0;
	pattern_beat_time_milliseconds = 0L;
	timer_update_balls = NULL;
	stopwatch_update_balls = NULL;

	// Empty state due to reset.
	state = PH_STATE_EMPTY;
}

void DisplayPatternHandler::Populate(const SiteswapPattern& pattern)
{
	Reset();

	// Populate with the new pattern.

	display_pattern = new DisplayPattern(pattern);

	if (display_pattern->IsValid())
	{
		// Passed test.

		is_valid = true;
		num_balls = display_pattern->GetNumberBalls();
		data_balls = new DisplayPatternBall[num_balls];

		timer_update_balls = new wxTimer(this, TIMER_BALLS_UPDATE);
		stopwatch_update_balls = new wxStopWatch();

		Calculate_PatternBeatTime_Milliseconds();

		// Set state.

		state = PH_STATE_STOP;
	}

	// Now populate all of the associated windows.

	for (auto i = windows.begin(); i != windows.end(); i++)
	{
		(*i)->Populate();
	}
}



// Control functions.



void DisplayPatternHandler::Play(wxCommandEvent& e)
{
	switch (state)
	{
	case PH_STATE_STOP:
	case PH_STATE_PAUSE:
	{
		state = PH_STATE_PLAY;
		OnBallsUpdate_ProcessNextActions();
		OnBallsUpdate_CheckSpeed(false);
		StartTimers();

		// Now play all the associated windows.

		for (auto i = windows.begin(); i != windows.end(); i++)
		{
			(*i)->Play();
		}
	}
	break;
	}
}

void DisplayPatternHandler::Stop(wxCommandEvent& e)
{
	switch (state)
	{
	case PH_STATE_PLAY:
	case PH_STATE_PAUSE:
	{
		StopTimers();

		// Reset class elements.

		for (unsigned int i = 0; i < num_balls; i++)
		{
			data_balls[i].Ball_StateRemoved();
		}

		mapping_current = 0;

		// Set state.

		state = PH_STATE_STOP;

		// Now stop all the associated windows.

		for (auto i = windows.begin(); i != windows.end(); i++)
		{
			(*i)->Stop();
		}
	}
	break;
	}
}

void DisplayPatternHandler::Pause(wxCommandEvent& e)
{
	switch (state)
	{
	case PH_STATE_PLAY:
	{
		update_balls_to_pause = 0;
		state = PH_STATE_PAUSE_TRANSIT;
	}
	break;
	}
}

void DisplayPatternHandler::PlayOnce_Forward(wxCommandEvent & e)
{
	switch (state)
	{
	case PH_STATE_STOP:
	case PH_STATE_PAUSE:
	{
		// Call Play first.
		Play(e);

		// Modify state.
		update_balls_to_pause = 0;
		state = PH_STATE_SINGLE_BEAT_FORWARD;
	}
	break;
	}
}

void DisplayPatternHandler::SpeedChange_Half(wxCommandEvent & e)
{
	if (speed != SPD_HALF && speed_change != SPD_CHG_HALF)
	{
		speed_change = SPD_CHG_HALF;
	}
}

void DisplayPatternHandler::SpeedChange_Normal(wxCommandEvent & e)
{
	if (speed != SPD_NORMAL && speed_change != SPD_CHG_NORMAL)
	{
		speed_change = SPD_CHG_NORMAL;
	}
}

void DisplayPatternHandler::SpeedChange_Double(wxCommandEvent & e)
{
	if (speed != SPD_DOUBLE && speed_change != SPD_CHG_DOUBLE)
	{
		speed_change = SPD_CHG_DOUBLE;
	}
}

bool DisplayPatternHandler::IsValid()
{
	return is_valid;
}

const DisplayPattern * DisplayPatternHandler::GetDisplayPattern()
{
	DisplayPattern * return_value = NULL;

	if (is_valid)
	{
		return_value = display_pattern;
	}

	return return_value;
}

unsigned int DisplayPatternHandler::GetMappingCurrent()
{
	unsigned int return_value = 0;

	if (is_valid)
	{
		return_value = mapping_current;
	}

	return return_value;
}

unsigned int DisplayPatternHandler::GetNumberBalls()
{
	unsigned int return_value = 0;

	if (is_valid)
	{
		return_value = num_balls;
	}

	return return_value;
}

long DisplayPatternHandler::GetStopwatch()
{
	long return_value = 0L;

	if (is_valid)
	{
		return_value = stopwatch_update_balls->Time();
	}

	return return_value;
}

long DisplayPatternHandler::GetPatternBeatTimeMilliseconds()
{
	long return_value = 0L;

	if (is_valid)
	{
		return_value = pattern_beat_time_milliseconds;
	}

	return return_value;
}

const DisplayPatternBall * DisplayPatternHandler::GetBall(const unsigned int & index)
{
	DisplayPatternBall * return_value = NULL;

	if (is_valid)
	{
		if (index >= 0 && index < num_balls)
		{
			return_value = &(data_balls[index]);
		}
	}

	return return_value;
}
