#pragma once
#include <functional>

class TimeEventFunction
{
public:
	float Time = 0.0f;
	float MaxTime = 0.0f;
	std::function<void()> Event;
	float DuringTime = -1.0f;
	bool Loop = false;
};

class UTimeEvent
{
public:
	UTimeEvent();
	~UTimeEvent();

	UTimeEvent(const UTimeEvent& _Other) = delete;
	UTimeEvent(UTimeEvent&& _Other) noexcept = delete;
	UTimeEvent& operator=(const UTimeEvent& _Other) = delete;
	UTimeEvent& operator=(UTimeEvent&& _Other) noexcept = delete;

	void PushEvent(float _Time, std::function<void()> _Function, float _DuringTime = -1.0f, bool _Loop = true)
	{
		Events.push_front({ _Time, _Time, _Function, _DuringTime, _Loop });
	}

	void Update(float _DeltaTime)
	{
		std::list<TimeEventFunction>::iterator StartIter = Events.begin();
		std::list<TimeEventFunction>::iterator EndIter = Events.end();

		for (; StartIter != EndIter; )
		{
			TimeEventFunction& TimeEvent = *StartIter;
			TimeEvent.Time -= _DeltaTime;
			if (-1 != TimeEvent.DuringTime)
			{
				TimeEvent.DuringTime -= _DeltaTime;
			}

			if (0.0f >= TimeEvent.DuringTime)
			{
				TimeEvent.Event();

				StartIter = Events.erase(StartIter);
			}			
			else if (0.0f >= TimeEvent.Time)
			{
				TimeEvent.Event();
				if (false == TimeEvent.Loop)
				{
					StartIter = Events.erase(StartIter);
				}
				else
				{
					++StartIter;
					TimeEvent.Time = TimeEvent.MaxTime;
				}
			}
			else {
				++StartIter;
			}
		}
	}

protected:

private:
	std::list<TimeEventFunction> Events;

};