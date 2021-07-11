#include "Settings.h"

#include "DisplayPatternHandler.h"

#include "DisplayPatternWindow.h"


static const int TIMER_BALLS_UPDATE = 2;

static const int BUTTON_PLAY = 1;
static const int BUTTON_STOP = 2;
static const int BUTTON_PAUSE = 3;
static const int BUTTON_PLAY_ONCE_FORWARD = 4;
static const int BUTTON_SPEED_CHANGE_DOWN = 5;
static const int BUTTON_SPEED_CHANGE_UP = 6;
static const int BUTTON_RESET = 7;



wxBEGIN_EVENT_TABLE(DisplayPatternHandler, wxEvtHandler)

EVT_TIMER(TIMER_BALLS_UPDATE, DisplayPatternHandler::OnBallsUpdate)
EVT_BUTTON(BUTTON_PLAY, DisplayPatternHandler::Play)
EVT_BUTTON(BUTTON_STOP, DisplayPatternHandler::Stop)
EVT_BUTTON(BUTTON_PAUSE, DisplayPatternHandler::Pause)
EVT_BUTTON(BUTTON_PLAY_ONCE_FORWARD, DisplayPatternHandler::PlayOnce_Forward)
EVT_BUTTON(BUTTON_SPEED_CHANGE_DOWN, DisplayPatternHandler::SpeedChange_Down)
EVT_BUTTON(BUTTON_SPEED_CHANGE_UP, DisplayPatternHandler::SpeedChange_Up)
EVT_BUTTON(BUTTON_RESET, DisplayPatternHandler::Reset)

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

	long pbtm = Settings::Pattern_BeatTime_Milliseconds();
	
	if (num_actions > 1U)
	{
		pbtm *= Settings::Pattern_BeatTime_Increase_MultiFactor();
	}

	pbtm *= speed_factor;

	if (pbtm == 0L) { pbtm = 1L; }

	pattern_beat_time_milliseconds = pbtm;
}

void DisplayPatternHandler::UpdateButtonStatesActions()
{
	btnPlay->Enable(
		state == DisplayPatternHandlerState::PH_STATE_PAUSE ||
		state == DisplayPatternHandlerState::PH_STATE_STOP
	);

	btnStop->Enable(
		state != DisplayPatternHandlerState::PH_STATE_STOP &&
		state != DisplayPatternHandlerState::PH_STATE_EMPTY
	);

	btnPause->Enable(
		state == DisplayPatternHandlerState::PH_STATE_PLAY
	);

	btnPlayOnceForward->Enable(
		state == DisplayPatternHandlerState::PH_STATE_PAUSE
	);

	btnReset->Enable(
		state != DisplayPatternHandlerState::PH_STATE_EMPTY
	);
}

void DisplayPatternHandler::UpdateButtonStatesSpeedChanges()
{
	btnSpeedChangeDown->Enable(
		state != DisplayPatternHandlerState::PH_STATE_EMPTY &&
		speed != DisplayPatternHandlerSpeed::SPD_HALF
	);

	btnSpeedChangeUp->Enable(
		state != DisplayPatternHandlerState::PH_STATE_EMPTY &&
		speed != DisplayPatternHandlerSpeed::SPD_DOUBLE
	);
}


void DisplayPatternHandler::SetState(DisplayPatternHandlerState stateUpdate)
{
	state = stateUpdate;
	UpdateButtonStatesActions();
	UpdateButtonStatesSpeedChanges();
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
				SetState(DisplayPatternHandlerState::PH_STATE_PAUSE);
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
				(*i)->OnBallsUpdate_DisplayPattern();
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
				UpdateButtonStatesSpeedChanges();
				
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
	btnPlay(NULL),
	btnStop(NULL),
	btnPause(NULL),
	btnPlayOnceForward(NULL),
	btnSpeedChangeDown(NULL),
	btnSpeedChangeUp(NULL),
	btnReset(NULL),
	state(PH_STATE_EMPTY),
	speed(SPD_NORMAL),
	speed_change(SPD_CHG_NONE),
	display_pattern(NULL),
	is_valid(false),
	num_balls(0U),
	num_actions(0U),
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

	btnPlay = new wxButton(this, BUTTON_PLAY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btnStop = new wxButton(this, BUTTON_STOP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btnPause = new wxButton(this, BUTTON_PAUSE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btnPlayOnceForward = new wxButton(this, BUTTON_PLAY_ONCE_FORWARD, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btnSpeedChangeDown = new wxButton(this, BUTTON_SPEED_CHANGE_DOWN, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btnSpeedChangeUp = new wxButton(this, BUTTON_SPEED_CHANGE_UP, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
	btnReset = new wxButton(this, BUTTON_RESET, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);
 
	btnPlay->SetBitmapLabel(wxBITMAP_PNG(IDB_PLAY_ENABLED));
	btnPlay->SetBitmapDisabled(wxBITMAP_PNG(IDB_PLAY_DISABLED));
	btnPlay->SetBitmapPressed(wxBITMAP_PNG(IDB_PLAY_PRESSED));

	btnStop->SetBitmapLabel(wxBITMAP_PNG(IDB_STOP_ENABLED));
	btnStop->SetBitmapDisabled(wxBITMAP_PNG(IDB_STOP_DISABLED));
	btnStop->SetBitmapPressed(wxBITMAP_PNG(IDB_STOP_PRESSED));

	btnPause->SetBitmapLabel(wxBITMAP_PNG(IDB_PAUSE_ENABLED));
	btnPause->SetBitmapDisabled(wxBITMAP_PNG(IDB_PAUSE_DISABLED));
	btnPause->SetBitmapPressed(wxBITMAP_PNG(IDB_PAUSE_PRESSED));

	btnPlayOnceForward->SetBitmapLabel(wxBITMAP_PNG(IDB_FORWARD_ENABLED));
	btnPlayOnceForward->SetBitmapDisabled(wxBITMAP_PNG(IDB_FORWARD_DISABLED));
	btnPlayOnceForward->SetBitmapPressed(wxBITMAP_PNG(IDB_FORWARD_PRESSED));

	btnSpeedChangeDown->SetBitmapLabel(wxBITMAP_PNG(IDB_SPEED_DOWN_ENABLED));
	btnSpeedChangeDown->SetBitmapDisabled(wxBITMAP_PNG(IDB_SPEED_DOWN_DISABLED));
	btnSpeedChangeDown->SetBitmapPressed(wxBITMAP_PNG(IDB_SPEED_DOWN_PRESSED));

	btnSpeedChangeUp->SetBitmapLabel(wxBITMAP_PNG(IDB_SPEED_UP_ENABLED));
	btnSpeedChangeUp->SetBitmapDisabled(wxBITMAP_PNG(IDB_SPEED_UP_DISABLED));
	btnSpeedChangeUp->SetBitmapPressed(wxBITMAP_PNG(IDB_SPEED_UP_PRESSED));

	btnReset->SetBitmapLabel(wxBITMAP_PNG(IDB_RESET_ENABLED));
	btnReset->SetBitmapDisabled(wxBITMAP_PNG(IDB_RESET_DISABLED));
	btnReset->SetBitmapPressed(wxBITMAP_PNG(IDB_RESET_PRESSED));
	
	sz_button_controls->Add(btnPlay);
	sz_button_controls->Add(btnStop);
	sz_button_controls->Add(btnPause);
	sz_button_controls->Add(btnPlayOnceForward);
	sz_button_controls->Add(btnSpeedChangeDown);
	sz_button_controls->Add(btnSpeedChangeUp);
	sz_button_controls->Add(btnReset);

	UpdateButtonStatesActions();
	UpdateButtonStatesSpeedChanges();

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
	num_balls = 0U;
	num_actions = 0U;
	update_balls_to_pause = -1;
	data_balls = NULL;
	mapping_current = 0;
	pattern_beat_time_milliseconds = 0L;
	timer_update_balls = NULL;
	stopwatch_update_balls = NULL;

	SetState(PH_STATE_EMPTY);
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
		num_actions = display_pattern->GetNumberActions();
		data_balls = new DisplayPatternBall[num_balls];

		timer_update_balls = new wxTimer(this, TIMER_BALLS_UPDATE);
		stopwatch_update_balls = new wxStopWatch();

		Calculate_PatternBeatTime_Milliseconds();

		SetState(PH_STATE_STOP);
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
		SetState(PH_STATE_PLAY);
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

		SetState(PH_STATE_STOP);

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
		SetState(PH_STATE_PAUSE_TRANSIT);
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
		SetState(PH_STATE_SINGLE_BEAT_FORWARD);
	}
	break;
	}
}

void DisplayPatternHandler::SpeedChange_Down(wxCommandEvent & e)
{
	if (speed_change == SPD_CHG_NONE && speed != SPD_HALF)
	{
		if (speed == SPD_DOUBLE)
		{
			speed_change = SPD_CHG_NORMAL;
		}
		else if (speed == SPD_NORMAL)
		{
			speed_change = SPD_CHG_HALF;
		}
	}
}

void DisplayPatternHandler::SpeedChange_Up(wxCommandEvent & e)
{
	if (speed_change == SPD_CHG_NONE && speed != SPD_DOUBLE)
	{
		switch (speed)
		{
		case SPD_NORMAL:
			speed_change = SPD_CHG_DOUBLE;
			break;
		case SPD_HALF:
			speed_change = SPD_CHG_NORMAL;
			break;
		default:
			break;
		}
	}
}

void DisplayPatternHandler::Reset(wxCommandEvent & e)
{
	Reset();
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
