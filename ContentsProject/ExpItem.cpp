#include "PreCompile.h"
#include "ExpItem.h"

AExpItem::AExpItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("ExpItem.png");
		SpriteRenderer->SetSpriteScale(1.0f);
	}
}

AExpItem::~AExpItem()
{
}

void AExpItem::SetLocation(FVector2D _Pos)
{
	Pos = _Pos;
	SetActorLocation(Pos);
}
