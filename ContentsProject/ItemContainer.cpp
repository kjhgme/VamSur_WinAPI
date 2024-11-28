#include "PreCompile.h"
#include "ItemContainer.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineSound.h>
#include "DropItem.h"
#include "Weapon.h"
#include "FloorChickenItem.h"
#include "RichCoinBagItem.h"
#include "OrologionItem.h"
#include "VacuumItem.h"
#include "RosaryItem.h"
#include "TantoItem.h"
#include "GoldItem.h"
#include "ExpItem.h"

AItemContainer::AItemContainer()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("ItemContainer", 0);
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::ITEMCONTAINER));
		SpriteRenderer->SetSpriteScale(1.0f);

		SpriteRenderer->CreateAnimation("Idle", "ItemContainer", 0, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("Idle");
		SpriteRenderer->CreateAnimation("Damaged", "ItemContainer", 3, 3, 0.5f);
	}
	{
		FVector2D scale = SpriteRenderer->GetComponentScale();
		scale.Y = scale.X;

		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 0.0f, 10.0f });
		CollisionComponent->SetComponentScale(scale);
		CollisionComponent->SetCollisionGroup(ECollisionGroup::ItemContainerBody);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		CollisionComponent->SetCollisionEnter(std::bind(&AItemContainer::CollisionEnter, this, std::placeholders::_1));

	}

	SetActorLocation(FVector2D::ZERO);
}

AItemContainer::~AItemContainer()
{
}

void AItemContainer::BeginPlay()
{
	Super::BeginPlay();

	DebugOn();
}

void AItemContainer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AItemContainer::CollisionEnter(AActor* _ColActor)
{
	AWeapon* Weapon = static_cast<AWeapon*>(_ColActor);
	
	Hp -= Weapon->AttackPower;
	SpriteRenderer->ChangeAnimation("Damaged");

	USoundPlayer HitSoundPlayer = UEngineSound::Play("Hit.wav");

	if (Hp <= 0)
	{
		SpawnDropItem();
		Destroy(0.1f);
	}

	TimeEventer.PushEvent(0.1f, std::bind(&AItemContainer::ChangeIdle, this), false, -1.0f, false);
}

void AItemContainer::ChangeIdle()
{
	SpriteRenderer->ChangeAnimation("Idle");
}

void AItemContainer::SpawnDropItem()
{
	typedef AActor* (*ItemSpawner)(ULevel*);

	auto SpawnGoldItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<AGoldItem>();
		};
	auto SpawnRichCoinBagItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<ARichCoinBagItem>();
		};
	auto SpawnRosaryItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<ARosaryItem>();
		};
	auto SpawnTantoItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<ATantoItem>();
		};
	auto SpawnOrologionItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<AOrologionItem>();
		};
	auto SpawnVacuumItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<AVacuumItem>();
		};
	auto SpawnFloorChickenItem = [](ULevel* World) -> AActor* {
		return World->SpawnActor<AFloorChickenItem>();
		};

	ItemSpawner Spawners[] = {
		SpawnGoldItem,
		SpawnRichCoinBagItem,
		SpawnRosaryItem,
		SpawnTantoItem,
		SpawnOrologionItem,
		SpawnVacuumItem,
		SpawnFloorChickenItem
	};

	ADropItem* SpawnItem = static_cast<ADropItem*>(GetWorld()->SpawnActor<ATantoItem>());
	SpawnItem->InitDropItem(GetActorLocation());

	/*UEngineRandom RandomGenerator;
	int ItemType = RandomGenerator.RandomInt(0, sizeof(Spawners) / sizeof(Spawners[0]) - 1);

	if (ItemType >= 0 && ItemType < sizeof(Spawners) / sizeof(Spawners[0]))
	{
		ADropItem* SpawnItem = static_cast<ADropItem*>(Spawners[ItemType](GetWorld()));

		SpawnItem->InitDropItem(GetActorLocation());
	}*/
}