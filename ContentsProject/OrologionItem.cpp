#include "PreCompile.h"
#include "OrologionItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

AOrologionItem::AOrologionItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Orologion", 0);
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
		SpriteRenderer->CreateAnimation("OrologionAnim", "Orologion", 0, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("OrologionAnim");
	}
}

AOrologionItem::~AOrologionItem()
{
}

void AOrologionItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();
}
