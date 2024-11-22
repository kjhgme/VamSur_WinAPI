#pragma once
#include <functional>

class TimeEventFunction
{
public:
	float Time = 0.0f;
	float MaxTime = 0.0f;
	std::function<void()> Event;
	bool IsUpdate = false;
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

	// 횟수and시간, 함수, 틱마다실행, 실행시간, 루프
	void PushEvent(float _Time, std::function<void()> _Function, bool _IsUpdate = false, float _DuringTime = -1.0f, bool _Loop = true)
	{
		Events.push_front({ _Time, _Time, _Function, _IsUpdate, _DuringTime, _Loop });
	}

	void Update(float _DeltaTime)
	{
		std::list<TimeEventFunction>::iterator StartIter = Events.begin();
		std::list<TimeEventFunction>::iterator EndIter = Events.end();

		for (; StartIter != EndIter; )
		{
			TimeEventFunction& TimeEvent = *StartIter;
			TimeEvent.Time -= _DeltaTime;

			if (true == TimeEvent.IsUpdate && 0.0f < TimeEvent.Time)
			{
				TimeEvent.Event();
			}
			else if (true == TimeEvent.IsUpdate && 0.0f >= TimeEvent.Time)
			{
				TimeEvent.Event();
				StartIter = Events.erase(StartIter);
				continue;
			}
			
			if(0.0f <= TimeEvent.DuringTime && false == TimeEvent.IsUpdate)
			{
				TimeEvent.DuringTime -= _DeltaTime;
				
				if (0.0f >= TimeEvent.Time)
				{
					TimeEvent.Event();
					TimeEvent.Time = TimeEvent.MaxTime;
				}
				if (0.0f >= TimeEvent.DuringTime)
				{
					StartIter = Events.erase(StartIter);
					continue;
				}				
			}
			else {
				if (false == TimeEvent.Loop && 0.0f >= TimeEvent.Time)
				{
					TimeEvent.Event();
					StartIter = Events.erase(StartIter);
					continue;
				}
				else if (true == TimeEvent.Loop && 0.0f >= TimeEvent.Time)
				{
					TimeEvent.Event();
					TimeEvent.Time = TimeEvent.MaxTime;
				}
			}

			++StartIter;
		}
	}

protected:

private:
	std::list<TimeEventFunction> Events;

};