#include "PreCompile.h"
#include "TitleImelda.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ATitleImelda::ATitleImelda()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 1.23f, WindowSize.Y / 2 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleImelda.png");
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 2);
	SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetAlphafloat(FadeValue);

	TimeEventer.PushEvent(5.0f, std::bind(&ATitleImelda::FadeIn, this), true, 2.5f, false);
}

ATitleImelda::~ATitleImelda()
{
}

void ATitleImelda::FadeIn()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 0.5f;
	FadeValue = UEngineMath::Clamp(FadeValue, 0.0f, 0.5f);
	SpriteRenderer->SetAlphafloat(FadeValue);
}

