#include "PreCompile.h"
#include "TantoItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"
#include "TantoSkill.h"

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

void ATantoItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	FVector2D pos = GetWorld()->GetMainPawn()->GetActorLocation();
	ATantoSkill* Fire = GetWorld()->SpawnActor<ATantoSkill>();
	Fire->SetActorLocation(pos);
}