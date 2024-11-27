#include "PreCompile.h"
#include "VacuumItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

AVacuumItem::AVacuumItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Vacuum", 0);
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

AVacuumItem::~AVacuumItem()
{
}
