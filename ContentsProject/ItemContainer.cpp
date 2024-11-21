#include "PreCompile.h"
#include "ItemContainer.h"
#include "ContentsEnum.h"

#include <EngineCore/2DCollision.h>
#include "DropItem.h"
#include "ExpItem.h"
#include "Weapon.h"

AItemContainer::AItemContainer()
{
}

AItemContainer::~AItemContainer()
{
}

void AItemContainer::BeginPlay()
{
	Super::BeginPlay();
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
	// ADropItem* DropItem = GetWorld()->SpawnActor<ADropItem>();

	AExpItem* newExpItem = GetWorld()->SpawnActor<AExpItem>();
	newExpItem->InitDropItem(GetActorLocation());
	newExpItem->SetExp(10);
}
