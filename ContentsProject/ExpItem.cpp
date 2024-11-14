#include "PreCompile.h"
#include "ExpItem.h"
#include "ContentsEnum.h"

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

void AExpItem::SetExp(float _Exp)
{
	Exp = _Exp;
}
