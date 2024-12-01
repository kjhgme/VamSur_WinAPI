#include "PreCompile.h"
#include "VacuumItem.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

#include "InGameMode.h"

AVacuumItem::AVacuumItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Vacuum", 0);
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
		SpriteRenderer->CreateAnimation("VacuumAnim", "Vacuum", 0, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("VacuumAnim");
	}
}

AVacuumItem::~AVacuumItem()
{
}

void AVacuumItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	GetSoundPlayer = UEngineSound::Play("sfx_chicken.wav");

	int size = AInGameMode::DropedExpItems.size();
	float deltaTime = UEngineAPICore::GetCore()->GetDeltaTime();

	for (int i = 0; i < size; ++i)
	{
		AInGameMode::DropedExpItems[i]->IsPickedUp = true;
		AInGameMode::DropedExpItems[i]->ItemToPlayer(deltaTime);
	}
}
