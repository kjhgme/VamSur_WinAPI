#include "PreCompile.h"
#include "DropItem.h"
#include "ContentsEnum.h"

// #include <EngineCore/EngineCoreDebug.h>

ADropItem::ADropItem()
{
}

ADropItem::~ADropItem()
{
}

void ADropItem::InitDropItem(FVector2D _Pos)
{
	SetActorLocation(_Pos);

	InitCollision(_Pos);

	DebugOn();
}

void ADropItem::InitCollision(FVector2D _Pos)
{
	FVector2D scale = SpriteRenderer->GetComponentScale();

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({0.0f, 0.0f});
	CollisionComponent->SetComponentScale(scale);
	CollisionComponent->SetCollisionGroup(ECollisionGroup::DropItemBody);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	CollisionComponent->SetCollisionEnter(std::bind(&ADropItem::CollisionEnter, this, std::placeholders::_1));
}

void ADropItem::CollisionEnter(AActor* _ColActor)
{
	Destroy();
}
