#include "PreCompile.h"
#include "GoldItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

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
