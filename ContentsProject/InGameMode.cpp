#include "PreCompile.h"
#include "InGameMode.h"

#include <EngineCore/Level.h>

#include "PlayMap.h"
#include "InfiniteMap.h"

AInGameMode::AInGameMode()
{
}

AInGameMode::~AInGameMode()
{
}

void AInGameMode::BeginPlay()
{
	AInfiniteMap* PMAP0 = GetWorld()->SpawnActor<AInfiniteMap>();
}
