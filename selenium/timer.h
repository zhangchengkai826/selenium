#pragma once

class Timer
{
public:
	Timer();
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.

private:
	double mSecondsPerCount;
	bool mStopped;
	__int64 mPausedTime;  // Total elapsed counter value when timer stopped
	__int64 mStopTime;  // The counter value when timer stopped
};