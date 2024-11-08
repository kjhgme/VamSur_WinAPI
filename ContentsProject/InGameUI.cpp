#include "PreCompile.h"
#include "InGameUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

AInGameUI::AInGameUI()
{
}

AInGameUI::~AInGameUI()
{
}

void AInGameUI::BeginPlay()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.Half().X, -400.0f });

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("InGameUI_LevelBar.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}
}

	void AInGameUI::Tick(float _DeltaTime)
{
}

	void AInGameUI::SetPos()
	{
	}
