#ifndef DISPLAY_PATTERN_HANDLER_H
#define DISPLAY_PATTERN_HANDLER_H

#include "stdafx.h"

#include <wx\wx.h>

#include "Enum.h"
#include "Struct.h"
#include "DisplayPattern.h"
#include "DisplayPatternBall.h"

class DisplayPatternWindow;

class DisplayPatternHandler : public wxWindow
{

private:

	wxButton
		* btnPlay,
		* btnStop,
		* btnPause,
		* btnPlayOnceForward,
		* btnSpeedChangeDown,
		* btnSpeedChangeUp,
		* btnReset;

	DisplayPatternHandlerState state;
	DisplayPatternHandlerSpeed speed;
	DisplayPatternHandlerSpeedChange speed_change;

	DisplayPattern * display_pattern;
	bool is_valid;

	unsigned int num_balls, num_actions;

	int update_balls_to_pause;

	DisplayPatternBall * data_balls;

	unsigned int mapping_current;

	long pattern_beat_time_milliseconds;

	wxTimer * timer_update_balls;
	wxStopWatch * stopwatch_update_balls;

	std::vector<DisplayPatternWindow *> windows;

	void StartTimers();
	void StopTimers();
	void Calculate_PatternBeatTime_Milliseconds();

	void OnBallsUpdate_CheckPause();
	void OnBallsUpdate_ProcessNextActions();
	void OnBallsUpdate_CheckSpeed(bool);

	void OnBallsUpdate(wxTimerEvent &);

	void Reset();

	void SetState(DisplayPatternHandlerState stateUpdate);
	void UpdateButtonStatesActions();
	void UpdateButtonStatesSpeedChanges();

	// Control functions.

	void Play(wxCommandEvent&);
	void Stop(wxCommandEvent&);
	void Pause(wxCommandEvent&);
	void PlayOnce_Forward(wxCommandEvent&);
	void SpeedChange_Down(wxCommandEvent&);
	void SpeedChange_Up(wxCommandEvent&);
	void Reset(wxCommandEvent&);

	wxDECLARE_EVENT_TABLE();

public:

	DisplayPatternHandler(wxWindow *);
	virtual ~DisplayPatternHandler();

	void AddWindow(DisplayPatternWindow *);
	void RemoveWindow(DisplayPatternWindow *);

	void Populate(const SiteswapPattern&);
	
	bool IsValid();
	const DisplayPattern * GetDisplayPattern();
	unsigned int GetMappingCurrent();
	unsigned int GetNumberBalls();
	long GetStopwatch();
	long GetPatternBeatTimeMilliseconds();
	const DisplayPatternBall * GetBall(const unsigned int &);
};

#endif
