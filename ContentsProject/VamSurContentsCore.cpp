#include "PreCompile.h"
#include "VamSurContentsCore.h"
#include <EngineCore/EngineAPICore.h>

#include "InGameMode.h"
#include "Player.h"

VamSurContentsCore::VamSurContentsCore()
{
}

VamSurContentsCore::~VamSurContentsCore()
{
}

void VamSurContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VampireSurvivors");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });

	//UEngineAPICore::GetCore()->CreateLevel<AInGameMode, APlayer>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AInGameMode, APlayer>("InGame");
	// UEngineAPICore::GetCore()->CreateLevel<AInGameMode, APlayer>("Result");
	
	UEngineAPICore::GetCore()->OpenLevel("InGame");
}

void VamSurContentsCore::Tick()
{
}