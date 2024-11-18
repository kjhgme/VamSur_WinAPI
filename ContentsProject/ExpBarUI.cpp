#include "PreCompile.h"
#include "ExpBarUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ExpBarUI::ExpBarUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetPos();

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("InGameUI_LevelBar.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);

		Scale = SpriteRenderer->GetComponentScale();
	}
}

ExpBarUI::~ExpBarUI()
{
}

void ExpBarUI::BeginPlay()
{
}

void ExpBarUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetPos();
}

void ExpBarUI::SetPos()
{
	Pos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
	Pos.Y = Pos.Y - WindowSize.Half().Y + Scale.Half().Y;

	SetActorLocation({ Pos });
}