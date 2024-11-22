#include "PreCompile.h"
#include "TantoItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

ATantoItem::ATantoItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("TantoItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

ATantoItem::~ATantoItem()
{
}
