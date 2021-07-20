#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <wx\wx.h>

#include "DisplayPatternWindow.h"

template<class T>
class SettingsWindow : public wxWindow
{

private:

	T eventGenerator;

	// Unique based on window/action.
	std::unordered_multimap<wxWindowID, unsigned int> mapControlsToActions;

	// Unique based on action (first entered is retained).
	std::unordered_map<unsigned int, wxEvent(T::*)()> mapActionsToEvents;

	std::unordered_set<DisplayPatternWindow*> windows;

	// Fires all stored events to a single window (used when a window is added).
	void GenerateEventsToWindow(wxWindow* window) const;

protected:

	T* const GetEventGenerator();
	void MapControlToAction(const wxWindowID& window, const unsigned int& action);
	void MapActionToEvent(const unsigned int& action, wxEvent(T::* generateEvent)());

	// Fires all events when a control is changed.
	void GenerateEventsForSource(const wxEvent& source) const;

	void ClearMappings();

public:

	SettingsWindow(wxWindow* parent);
	virtual ~SettingsWindow();

	void AddWindow(DisplayPatternWindow* window);
	void RemoveWindow(DisplayPatternWindow* window);

	void ClearWindows();

};

template<class T>
SettingsWindow<T>::SettingsWindow(wxWindow* parent)
	: wxWindow(parent, wxID_ANY),
	eventGenerator(),
	mapControlsToActions(),
	mapActionsToEvents(),
	windows()
{

}

template<class T>
SettingsWindow<T>::~SettingsWindow()
{

}

template<class T>
T* const SettingsWindow<T>::GetEventGenerator()
{
	return eventGenerator;
}

template<class T>
void SettingsWindow<T>::MapControlToAction(const wxWindowID& window, const unsigned int& action)
{
	auto range = mapControlsToActions.equal_range(window);
	bool found = false;

	for (auto i = range.first; i != range.second; i++)
	{
		if (i->second == action)
		{
			found = true;
			break;
		}
	};

	if (!found)
	{
		mapControlsToActions.emplace(window, action);
	}
}

template<class T>
void SettingsWindow<T>::MapActionToEvent(const unsigned int& action, wxEvent(T::* generateEvent)())
{
	if (mapActionsToEvents.find(action) == mapActionsToEvents.end())
	{
		mapActionsToEvents.insert(action, generateEvent);
	}
}

template<class T>
void SettingsWindow<T>::AddWindow(DisplayPatternWindow* window)
{
	if (window != NULL)
	{
		windows.insert(window);
	}
}

template<class T>
void SettingsWindow<T>::RemoveWindow(DisplayPatternWindow* window)
{
	if (window != NULL)
	{
		windows.erase(window);
	}
}

template<class T>
void SettingsWindow<T>::GenerateEventsToWindow(wxWindow* window) const
{
	for (auto i = mapActionsToEvents.begin(); i != mapActionsToEvents.end(); i++)
	{
		window->QueueEvent(eventGenerator.(*i)());
	}
}

template<class T>
void SettingsWindow<T>::GenerateEventsForSource(const wxEvent& source) const
{
	auto* object = source.GetEventObject();

	if (object != NULL && object->IsKindOf(wxCLASSINFO(wxWindow)))
	{
		const wxWindowID control = ((wxWindow*)(object))->GetId();
		// Test line.
		const int control_test = source.GetId();

		auto range = mapControlsToActions.equal_range(control);

		for (auto i = range.first; i != range.second; i++)
		{
			auto generateEvent = mapActionsToEvents.find(i->second);

			if (generateEvent != mapActionsToEvents.end())
			{
				for (auto j = windows.begin(); j != windows.end(); j++)
				{
					(*j)->QueueEvent(eventGenerator.(*generateEvent)());
				}
			}
		}
	}
}

template<class T>
void SettingsWindow<T>::ClearWindows()
{
	windows.clear();
}

template<class T>
void SettingsWindow<T>::ClearMappings()
{
	mapActionsToEvents.clear();
	mapControlsToActions.clear();
}

#endif
