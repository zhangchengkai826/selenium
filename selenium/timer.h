#pragma once

class Timer
{
public:
	Timer();

	float TotalTime()const; // in seconds
	float DeltaTime()const; // in seconds

	void Reset(); 
	void Start(); // Call when unpaused.
	void Stop();  // Call when paused.
	void Tick();  

private:
	double mSecondsPerCount;
	double mDeltaTime; // unit: second(s)

	__int64 mBaseTime; // unit: counter value
	__int64 mPausedTime;  // Total elapsed counter value when timer stopped
	__int64 mStopTime;  // The counter value when timer stopped
	__int64 mPrevTime; // unit: counter value
	__int64 mCurrTime;

	bool mStopped;
};