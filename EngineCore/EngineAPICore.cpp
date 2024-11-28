#include "PreCompile.h"
#include "EngineAPICore.h"

#include <Windows.h>

#include <EngineBase/EngineDelegate.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
	// MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Levels.clear();

	UEngineSound::Release();
}


int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// _CrtSetBreakAlloc(4263);

	UserCore = _UserCore;

	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));;
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

void UEngineAPICore::EngineTick()
{
	UserCore->Tick();

	MainCore->Tick();
}

void UEngineAPICore::Tick()
{
	if (true == IsCurLevelReset)
	{
		delete CurLevel;
		CurLevel = nullptr;
		IsCurLevelReset = false;
	}


	if (nullptr != NextLevel)
	{
		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		NextLevel->LevelChangeStart();

		NextLevel = nullptr;

		DeltaTimer.TimeStart();
		NonStopDeltaTimer.TimeStart();
	}

	DeltaTimer.TimeCheck();
	NonStopDeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	UEngineInput::GetInst().KeyCheck(DeltaTime);

	UEngineSound::Update();

	if (nullptr == CurLevel)
	{
		MSGASSERT("The engine core is not assigned a current level.(UEngineAPICore::EngineTick)");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	CurLevel->Render(DeltaTime);
	CurLevel->Collision(DeltaTime);
	CurLevel->Release(DeltaTime);
}

ULevel* UEngineAPICore::GetLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "is not exist.(UEngineAPICore::OpenLevel)");
	}

	return FindIter->second;
}

void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "is not exist.(UEngineAPICore::OpenLevel)");
		return;
	}

	CurLevel = FindIter->second;
}