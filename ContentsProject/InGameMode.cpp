#include "PreCompile.h"
#include "InGameMode.h"

#include <EngineCore/Level.h>

#include "Player.h"
#include "InGameUI.h"
#include "InfiniteMap.h"
#include "TitleGameMode.h"
#include "MonsterSpawner.h"
#include "ContentsEnum.h"

AInGameMode::AInGameMode()
{
}

AInGameMode::~AInGameMode()
{
}

void AInGameMode::BeginPlay()
{
	GetWorld()->CollisionGroupLink(ECollisionGroup::PlayerBody, ECollisionGroup::MonsterBody);
	GetWorld()->CollisionGroupLink(ECollisionGroup::WeaponBody, ECollisionGroup::MonsterBody);
	GetWorld()->CollisionGroupLink(ECollisionGroup::MonsterBody, ECollisionGroup::MonsterBody);

	AInfiniteMap* Map = GetWorld()->SpawnActor<AInfiniteMap>();
	AMonsterSpawner* MonsterSpawner = GetWorld()->SpawnActor<AMonsterSpawner>();
	AInGameUI* InGameUI = GetWorld()->SpawnActor<AInGameUI>();
	/*switch (ATitleGameMode::SelectedCharacter)
	{
	case 1:
		SelectCharacter("Antonio");
		break;
	default:
		SelectCharacter("Imelda");
		break;
	}*/

	SelectCharacter("Antonio");
}

void AInGameMode::SelectCharacter(std::string_view _Name)
{
	APlayer* player = GetWorld()->SpawnActor<APlayer>();
	player->PlayerInit(_Name);
}

