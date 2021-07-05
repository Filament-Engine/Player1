#pragma once
#include <SDL.h>
//  a class that can be used to determine fps
class Timer {
private:
	Uint32 mStartTicks; // the clock time when the timer stared
	bool mStarted; // if the timer has started
public:
	// constructor for the timer class
	Timer() {
		mStartTicks = 0;
		mStarted = false;
	}

	// starts counting
	void start() {
		mStarted = true; // sets the bool for started as true
		mStartTicks = SDL_GetTicks(); // gets the number of ticks for start ticks
	}

	// stops counting
	void stop() {
		mStarted = false; // stops the timer 

		mStartTicks = 0; // resets mStartTicks
	}

	// gets the time
	Uint32 getTicks() {
		//The actual timer time
		Uint32 time = 0;

		//If the timer is running
		if (mStarted)
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}

		return time;
	}
};