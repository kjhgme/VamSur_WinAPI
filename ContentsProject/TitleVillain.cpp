#include "PreCompile.h"
#include "TitleVillain.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

#include "ContentsEnum.h"

ATitleVillain::ATitleVillain()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 4.8f, WindowSize.Y / 1.4f });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleVillain.png");
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 1);
	SpriteRenderer->SetSpriteScale(1.0f);
}

ATitleVillain::~ATitleVillain()
{
}
