#include "PreCompile.h"
#include "PlayMap.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

APlayMap::APlayMap()
{
	USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSprite("Stage01.png");

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.5f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());
}

APlayMap::~APlayMap()
{
}

