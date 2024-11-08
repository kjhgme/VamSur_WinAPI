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


	// Function
	virtual bool IsActive()
	{
		return IsActiveValue && false == IsDestroyValue;
	}

	virtual bool IsDestroy()
	{
		return IsDestroyValue;
	}


protected:

private:
	std::string Name;

	bool IsDestroyValue = false;
	bool IsActiveValue = true;
};

