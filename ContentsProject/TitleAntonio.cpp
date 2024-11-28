#include "PreCompile.h"
#include "TitleAntonio.h"

#include <EngineCore/EngineAPICore.h>
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
	SpriteRenderer->SetAlphafloat(FadeValue);

	TimeEventer.PushEvent(5.0f, std::bind(&ATitleAntonio::FadeIn, this), true, 2.2f, false);
}

ATitleAntonio::~ATitleAntonio()
{
}

void ATitleAntonio::FadeIn()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 1.5f;
	FadeValue = UEngineMath::Clamp(FadeValue, 0.0f, 1.0f);
	SpriteRenderer->SetAlphafloat(FadeValue);
}
