#include "PreCompile.h"
#include "VacuumItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

AVacuumItem::AVacuumItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("VacuumItem_00.png");
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

AVacuumItem::~AVacuumItem()
{
}
