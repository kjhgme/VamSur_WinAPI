#include "PreCompile.h"
#include "VamSurContentsCore.h"
#include <EngineCore/EngineAPICore.h>

VamSurContentsCore::VamSurContentsCore()
{
}

VamSurContentsCore::~VamSurContentsCore()
{
}

void VamSurContentsCore::BeginPlay()
{
	UEngineAPICore::GetCore()->CreateLevel("Title");
	UEngineAPICore::GetCore()->CreateLevel("InGame");
	UEngineAPICore::GetCore()->CreateLevel("Result");
}

void VamSurContentsCore::Tick()
{
}