#include "PreCompile.h"
#include "RichCoinBagItem.h"
#include "ContentsEnum.h"

#include "InGameUI.h"

ARichCoinBagItem::ARichCoinBagItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("RichCoinBagItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

ARichCoinBagItem::~ARichCoinBagItem()
{
}

void ARichCoinBagItem::SetGold(int _Gold)
{
	Gold = _Gold;
}

void ARichCoinBagItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	AInGameUI::KillAndGold->AddGoldCount(Gold);
}
