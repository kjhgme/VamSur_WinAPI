#include "PreCompile.h"
#include "ExpItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

AExpItem::AExpItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("ExpItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

AExpItem::~AExpItem()
{
}

void AExpItem::SetExp(float _Exp)
{
	Exp = _Exp;
}

void AExpItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	AInGameMode::Player->AddExp(Exp);
}

