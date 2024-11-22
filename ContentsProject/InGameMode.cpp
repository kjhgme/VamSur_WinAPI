#include "PreCompile.h"
#include "InGameMode.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/Level.h>

#include "InGameUI.h"
#include "InfiniteMap.h"
#include "TitleGameMode.h"
#include "MonsterSpawner.h"
#include "ItemContainer.h"

APlayer* AInGameMode::Player = nullptr;

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
	GetWorld()->CollisionGroupLink(ECollisionGroup::DropItemBody, ECollisionGroup::PlayerBody);
	GetWorld()->CollisionGroupLink(ECollisionGroup::ItemContainerBody, ECollisionGroup::WeaponBody);

	Map = GetWorld()->SpawnActor<AInfiniteMap>();
	MonsterSpawner = GetWorld()->SpawnActor<AMonsterSpawner>();
	InGameUI = GetWorld()->SpawnActor<AInGameUI>();
	TimeEventer.PushEvent(1.0f, std::bind(&AInGameMode::SpawnItemContainer, this), false, -1.0f, true);
	
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
	Player = GetWorld()->SpawnActor<APlayer>();
	Player->PlayerInit(_Name);
}

void AInGameMode::SpawnItemContainer()
{
	UEngineRandom RandomGenerator;

	if (0 == RandomGenerator.RandomInt(0, 9))
	{
		AItemContainer* ItemContainer = GetWorld()->SpawnActor<AItemContainer>();
		ItemContainer->SetActorLocation(MonsterSpawner->GetActorLocation());
	}
}