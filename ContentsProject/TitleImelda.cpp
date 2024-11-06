#include "PreCompile.h"
#include "TitleImelda.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

#include "ContentsEnum.h"

ATitleImelda::ATitleImelda()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 1.23f, WindowSize.Y / 2 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleImelda.png");
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 2);
	SpriteRenderer->SetSpriteScale(1.0f);
}

ATitleImelda::~ATitleImelda()
{
}
