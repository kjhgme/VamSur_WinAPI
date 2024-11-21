#include "PreCompile.h"
#include "EngineTimer.h"


UEngineTimer::UEngineTimer()
{
	QueryPerformanceFrequency(&Count);

	TimeCounter = static_cast<double>(Count.QuadPart);

	QueryPerformanceCounter(&PrevTime);
	QueryPerformanceCounter(&CurTime);
}

UEngineTimer::~UEngineTimer()
{
}

void UEngineTimer::TimeStart()
{
	QueryPerformanceCounter(&PrevTime);
}

void UEngineTimer::TimeCheck()
{
	if (false == bIsTimeStopped)
	{
		QueryPerformanceCounter(&CurTime);

		double Tick = static_cast<double>(CurTime.QuadPart - PrevTime.QuadPart);
		DeltaTime = Tick / TimeCounter;
		fDeltaTime = static_cast<float>(DeltaTime);
		PrevTime.QuadPart = CurTime.QuadPart;
	}
}

float UEngineTimer::End()
{
	TimeCheck();
	return GetDeltaTime();
}

double UEngineTimer::DEnd()
{
	TimeCheck();
	return GetDoubleDeltaTime();
}

float UEngineTimer::GetIndependentDeltaTime()
{
	QueryPerformanceCounter(&IndependentCurTime);

	double Tick = static_cast<double>(IndependentCurTime.QuadPart - IndependentPrevTime.QuadPart);
	float IndependentDeltaTime = static_cast<float>(Tick / TimeCounter);

	IndependentPrevTime = IndependentCurTime;

	return IndependentDeltaTime;
}

void UEngineTimer::ToggleTime()
{
	if (true == bIsTimeStopped)
	{
		QueryPerformanceCounter(&PrevTime);
		bIsTimeStopped = false;
	}
	else
	{
		bIsTimeStopped = true; 
		DeltaTime = 0.0;
		fDeltaTime = 0.0f;
	}
}
