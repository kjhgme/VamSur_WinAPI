#include "PreCompile.h"
#include "PlayMap.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

APlayMap::APlayMap()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SetStage(0);

	FVector2D MapScale = SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetComponentLocation(MapScale.Half());
}

APlayMap::~APlayMap()
{
}