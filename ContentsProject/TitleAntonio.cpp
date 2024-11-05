#include "PreCompile.h"
#include "TitleAntonio.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWindow.h>

#include "ContentsEnum.h"

ATitleAntonio::ATitleAntonio()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 1.9f, WindowSize.Y / 1.3f });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleAntonio.png");
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 3);
	SpriteRenderer->SetSpriteScale(1.0f);
}

ATitleAntonio::~ATitleAntonio()
{
}
