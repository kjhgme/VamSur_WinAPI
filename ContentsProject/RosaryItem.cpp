#include "PreCompile.h"
#include "RosaryItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

ARosaryItem::ARosaryItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("RosaryItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

ARosaryItem::~ARosaryItem()
{
}
