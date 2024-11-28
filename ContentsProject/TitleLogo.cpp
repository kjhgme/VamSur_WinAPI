#include "PreCompile.h"
#include "TitleLogo.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ATitleLogo::ATitleLogo()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 1.95f, WindowSize.Y / 3.4f });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleLogo.png");
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 5);
	SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetAlphafloat(0.0f);

	TimeEventer.PushEvent(3.0f, std::bind(&ATitleLogo::Opening, this), false, -1.0f, false);
}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::Opening()
{
	SpriteRenderer->SetAlphafloat(1.0f);
}
