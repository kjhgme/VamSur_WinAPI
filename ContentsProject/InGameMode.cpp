#include "PreCompile.h"
#include "InGameMode.h"

#include <EngineCore/Level.h>

#include "Player.h"
#include "PlayMap.h"
#include "InfiniteMap.h"
#include "TitleGameMode.h"
#include "MonsterSpawner.h"

AInGameMode::AInGameMode()
{
}

AInGameMode::~AInGameMode()
{
}

void AInGameMode::BeginPlay()
{
	AInfiniteMap* PMAP0 = GetWorld()->SpawnActor<AInfiniteMap>();
	AMonsterSpawner* MonsterSpawner = GetWorld()->SpawnActor<AMonsterSpawner>();
	/*switch (ATitleGameMode::SelectedCharacter)
	{
	case 1:
		SelectCharacter("Antonio");
		break;
	default:
		SelectCharacter("Imelda");
		break;
	}*/
}

void AInGameMode::SelectCharacter(std::string_view _Name)
{
	APlayer* player = GetWorld()->SpawnActor<APlayer>();
	player->PlayerInit(_Name);
}

