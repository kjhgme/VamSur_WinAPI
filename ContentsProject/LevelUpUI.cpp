#include "PreCompile.h"
#include "LevelUpUI.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include "InGameUI.h"

LevelUpUI::LevelUpUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetPos();

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("InGameUI_LevelUpPanel.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
		SpriteRenderer->SetSpriteScale(1.0f);

		Scale = SpriteRenderer->GetComponentScale();
	}
}

LevelUpUI::~LevelUpUI()
{
}

void LevelUpUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('K'))
	{
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);

		UEngineAPICore::GetCore()->GetTimer().ToggleTime();
	}

	SetPos();
}

void LevelUpUI::SetPos()
{
	Pos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
	Pos.Y = Pos.Y - WindowSize.Half().Y + Scale.Half().Y;

	SetActorLocation({ Pos });
}

void LevelUpUI::SetActive()
{
	SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
}