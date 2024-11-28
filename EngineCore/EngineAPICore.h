#pragma once
#include <string>
#include <Windows.h>
#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

#include "Level.h"

class UContentsCore
{
public:
	virtual void BeginPlay() = 0;
	virtual void Tick() = 0;
};

class UEngineAPICore
{
public:
	UEngineAPICore();
	~UEngineAPICore();

	UEngineAPICore(const UEngineAPICore& _Other) = delete;
	UEngineAPICore(UEngineAPICore&& _Other) noexcept = delete;
	UEngineAPICore& operator=(const UEngineAPICore& _Other) = delete;
	UEngineAPICore& operator=(UEngineAPICore&& _Other) noexcept = delete;

	static int EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore);

	// GetFunction
	static class UEngineAPICore* GetCore()
	{
		return MainCore;
	}

	UEngineWindow& GetMainWindow()
	{
		return EngineMainWindow;
	}

	ULevel* GetCurLevel()
	{
		return CurLevel;
	}

	ULevel* GetLevel(std::string_view _LevelName);

	float GetDeltaTime()
	{
		return DeltaTimer.GetDeltaTime();
	}

	UEngineTimer& GetTimer()
	{
		return DeltaTimer;
	}


	// Function
	template<typename GameModeType, typename MainPawnType>
	ULevel* CreateLevel(std::string_view _LevelName)
	{
		ULevel* NewLevel = new ULevel();

		NewLevel->CreateGameMode<GameModeType, MainPawnType>();

		Levels.insert({ _LevelName.data() , NewLevel });

		return NewLevel;
	}
	
	template<typename GameModeType, typename MainPawnType>
	void ResetLevel(std::string_view _LevelName)
	{
		
		if (CurLevel->GetName() != _LevelName)
		{
			DestroyLevel(_LevelName);
			CreateLevel<GameModeType, MainPawnType>(_LevelName);
			return;
		}

		std::string LevelName = static_cast<std::string>(_LevelName);
		std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(LevelName);
		Levels.erase(FindIter);
		NextLevel = CreateLevel<GameModeType, MainPawnType>(_LevelName);
		IsCurLevelReset = true;
	}
	
	void DestroyLevel(std::string_view _LevelName)
	{
		std::string LevelName = static_cast<std::string>(_LevelName);

		if (false == Levels.contains(LevelName))
		{
			return;
		}

		std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(LevelName);

		if (nullptr != FindIter->second)
		{
			delete FindIter->second;
			FindIter->second = nullptr;
		}

		Levels.erase(FindIter);
	}


	void OpenLevel(std::string_view _LevelName);

protected:

private:
	static void EngineBeginPlay();
	static void EngineTick();
	static UEngineAPICore* MainCore;
	static UContentsCore* UserCore;

	UEngineWindow EngineMainWindow = UEngineWindow();
	UEngineTimer DeltaTimer = UEngineTimer();
	UEngineTimer NonStopDeltaTimer = UEngineTimer();

	std::map<std::string, class ULevel*> Levels;
	class ULevel* CurLevel = nullptr;
	class ULevel* NextLevel = nullptr;
	bool IsCurLevelReset = false;

	void Tick();
};