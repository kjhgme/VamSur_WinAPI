#include "PreCompile.h"
#include "TantoItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"
#include "TantoSkill.h"

ATantoItem::ATantoItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Tanto", 0);
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
	}
}

ATantoItem::~ATantoItem()
{
}

void ATantoItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	FVector2D pos = GetWorld()->GetMainPawn()->GetActorLocation();
	TantoSkill* Fire = GetWorld()->SpawnActor<TantoSkill>();
	Fire->SetActorLocation(pos);
}