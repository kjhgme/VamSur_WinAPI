#pragma once
#include <Windows.h>

// 설명 :
class UEngineTimer
{
public:
	UEngineTimer();
	~UEngineTimer();

	UEngineTimer(const UEngineTimer& _Other) = delete;
	UEngineTimer(UEngineTimer&& _Other) noexcept = delete;
	UEngineTimer& operator=(const UEngineTimer& _Other) = delete;
	UEngineTimer& operator=(UEngineTimer&& _Other) noexcept = delete;

	void TimeStart();
	void TimeCheck();

	float End();
	double DEnd();

	// GetFunction
	float GetDeltaTime()
	{
		return fDeltaTime;
	}

	double GetDoubleDeltaTime()
	{
		return DeltaTime;
	}

	float GetIndependentDeltaTime();

	// Function
	void ToggleTime();


protected:

private:
	LARGE_INTEGER Count = LARGE_INTEGER();
	LARGE_INTEGER PrevTime = LARGE_INTEGER();
	LARGE_INTEGER CurTime = LARGE_INTEGER();

	LARGE_INTEGER IndependentPrevTime = LARGE_INTEGER();
	LARGE_INTEGER IndependentCurTime = LARGE_INTEGER();

	double TimeCounter = 0.0f;

	double DeltaTime = 0.0;

	float fDeltaTime = 0.0f;

	bool bIsTimeStopped = false;
};

