#include "PreCompile.h"
#include "TitleVillain.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ATitleVillain::ATitleVillain()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 4.8f, WindowSize.Y / 1.4f });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleVillain.png");
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) + 1);
	SpriteRenderer->SetSpriteScale(1.0f);
	SpriteRenderer->SetAlphafloat(FadeValue);

	TimeEventer.PushEvent(5.0f, std::bind(&ATitleVillain::FadeIn, this), true, 2.0f, false);
}

ATitleVillain::~ATitleVillain()
{
}

void ATitleVillain::FadeIn()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 0.5f;
	FadeValue = UEngineMath::Clamp(FadeValue, 0.0f, 0.5f);
	SpriteRenderer->SetAlphafloat(FadeValue);
}