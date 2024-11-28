#include "PreCompile.h"
#include "GoldItem.h"
#include "ContentsEnum.h"

#include "InGameUI.h"

AGoldItem::AGoldItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("GoldItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

AGoldItem::~AGoldItem()
{
}

void AGoldItem::SetGold(int _Gold)
{
	Gold = _Gold;
}

void AGoldItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	AInGameUI::KillAndGold->AddGoldCount(Gold);

	GetSoundPlayer = UEngineSound::Play("sfx_coin.wav");
}
