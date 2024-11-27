#pragma once
#include <string>

class UObject
{
public:
	UObject();

	virtual ~UObject();

	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	// GetFunction
	std::string GetName() const
	{
		return Name;
	}

	std::string_view GetNameView() const
	{
		return Name.c_str();
	}

	// SetFunction
	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}
	
	void SetActive(bool _IsActive)
	{
		IsActiveValue = _IsActive;
	}


	// IsFunction
	virtual bool IsActive()
	{
		return IsActiveValue && false == IsDestroyValue;
	}

	virtual bool IsDestroy()
	{
		return IsDestroyValue;
	}

	bool IsDebug()
	{
		return IsDebugValue;
	}

	void DebugOn()
	{
		IsDebugValue = true;
	}

	void DebugOff()
	{
		IsDebugValue = false;
	}

	void DebugSwitch()
	{
		IsDebugValue = !IsDebugValue;
	}

	// Function
	void Destroy(float _Time = 0.0f)
	{
		DeathTime = _Time;

		if (0.0f < _Time)
		{
			IsDeathTimeCheck = true;
			return;
		}

		IsDestroyValue = true;
	}

	virtual void ReleaseCheck(float _DeltaTime)
	{

	}

	virtual void ReleaseTimeCheck(float _DeltaTime)
	{
		if (false == IsDeathTimeCheck)
		{
			return;
		}

		CurDeathTime += _DeltaTime;

		if (DeathTime <= CurDeathTime)
		{
			IsDestroyValue = true;
		}
	}

protected:

private:
	std::string Name;

	bool IsDestroyValue = false;
	bool IsActiveValue = true;
	bool IsDeathTimeCheck = false;
	bool IsDebugValue = false;

	float DeathTime = 0.0f;
	float CurDeathTime = 0.0f;
};

