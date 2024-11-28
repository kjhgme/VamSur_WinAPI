#include "PreCompile.h"
#include "TitleBG.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ATitleBG::ATitleBG()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 2, WindowSize.Y / 2 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleBG.png");
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSpriteScale(OpenScale);

	TimeEventer.PushEvent(2.0f, std::bind(&ATitleBG::Opening, this), true, -1.0f, false);
}

ATitleBG::~ATitleBG()
{
}

void ATitleBG::Opening()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	OpenScale -= DeltaTime * 5.0f;
	OpenScale = UEngineMath::Clamp(OpenScale, 1.0f, 10.0f);
	SpriteRenderer->SetSpriteScale(OpenScale);
}
