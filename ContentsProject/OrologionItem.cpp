#include "PreCompile.h"
#include "OrologionItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

AOrologionItem::AOrologionItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("OrologionItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

AOrologionItem::~AOrologionItem()
{
}
