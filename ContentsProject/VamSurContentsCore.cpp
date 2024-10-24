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
	// UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AInGameMode, APlayer>("InGame");
	// UEngineAPICore::GetCore()->CreateLevel<APlayGameMode, APlayer>("Result");

	UEngineAPICore::GetCore()->OpenLevel("InGame");
}

void VamSurContentsCore::Tick()
{
}