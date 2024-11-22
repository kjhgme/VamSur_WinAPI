#include "PreCompile.h"
#include "FloorChickenItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

AFloorChickenItem::AFloorChickenItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("FloorChickenItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

AFloorChickenItem::~AFloorChickenItem()
{
}

void AFloorChickenItem::SetHp(float _Hp)
{
	Hp = _Hp;
}

void AFloorChickenItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	AInGameMode::Player->AddHp(Hp);
}
