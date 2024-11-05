#include "PreCompile.h"
#include "ResultGameMode.h"

AResultGameMode::AResultGameMode()
{
}

AResultGameMode::~AResultGameMode()
{
}


void AResultGameMode::BeginPlay()
{
	Super::BeginPlay();
}


void AResultGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}
}