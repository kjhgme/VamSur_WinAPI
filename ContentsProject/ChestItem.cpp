#include "PreCompile.h"
#include "ChestItem.h"
#include "ContentsEnum.h"

#include "ChestUI.h"

AChestItem::AChestItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Box_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::ITEM) + 1);
	}
	{
		CursorRenderer = CreateDefaultSubObject<USpriteRenderer>();
		CursorRenderer->SetSprite("ChestCursor", 0);
		CursorRenderer->SetSpriteScale(1.0f);
		CursorRenderer->SetOrder(static_cast<int>(ERenderOrder::ITEM) + 1);
	}

	CursorRenderer->CreateAnimation("Chest_Idle", "ChestCursor", 0, 7, 0.05f);
	CursorRenderer->ChangeAnimation("Chest_Idle");
	CursorRenderer->AddComponentLocation({ 0.0f, -50.0f });
}

AChestItem::~AChestItem()
{
}

void AChestItem::InitCollision(FVector2D _Pos)
{
	FVector2D scale = SpriteRenderer->GetComponentScale();

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0.0f, 0.0f });
	CollisionComponent->SetComponentScale(scale);
	CollisionComponent->SetCollisionGroup(ECollisionGroup::DropItemBody);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	CollisionComponent->SetCollisionEnter(std::bind(&AChestItem::TakeChest, this));
}

void AChestItem::TakeChest()
{
	ApplyItemEffect();

	Destroy();
}

void AChestItem::ApplyItemEffect()
{
	ChestUI* CUI = GetWorld()->SpawnActor<ChestUI>();
}