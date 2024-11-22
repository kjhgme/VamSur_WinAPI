#include "PreCompile.h"
#include "RichCoinBagItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

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
