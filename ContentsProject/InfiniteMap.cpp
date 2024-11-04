#include "PreCompile.h"
#include "InfiniteMap.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

AInfiniteMap::AInfiniteMap()
{
	core = UEngineAPICore::GetCore();
	playerPos = core->GetCurLevel()->GetMainPawn()->GetActorLocation();

	for (int i = 0; i < 9; ++i)
	{
		USpriteRenderer* SpriteRenderer = new USpriteRenderer();
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);

		SetStage(SpriteRenderer, 0);

		MapScale = SpriteRenderer->SetSpriteScale(0.2f);
		SpriteRenderer->SetComponentLocation(MapScale * InfiMap.size());

		InfiMap.push_back(SpriteRenderer);
	}
}

AInfiniteMap::~AInfiniteMap()
{
	InfiMap.clear();
}

void AInfiniteMap::Tick(float _DeltaTime)
{
	playerPos = core->GetCurLevel()->GetMainPawn()->GetActorLocation();

	if (playerPos.X >= MapScale.X)
		int a = 0;
}

void AInfiniteMap::SetStage(USpriteRenderer* _SpriteRenderer, int _level)
{
	_SpriteRenderer->SetSprite("Stage", _level);
}

