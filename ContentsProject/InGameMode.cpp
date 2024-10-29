#include "PreCompile.h"
#include "InGameMode.h"

#include <EngineCore/Level.h>

#include "PlayMap.h"

AInGameMode::AInGameMode()
{
}

AInGameMode::~AInGameMode()
{
}

void AInGameMode::BeginPlay()
{
	APlayMap* PMAP0 = GetWorld()->SpawnActor<APlayMap>();
}
