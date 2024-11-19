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
		MainPanelRenderer = CreateDefaultSubObject<USpriteRenderer>();
		MainPanelRenderer->SetSprite("InGameUI_LevelUpPanel.png");
		MainPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
		MainPanelRenderer->SetSpriteScale(1.0f);

		Scale = MainPanelRenderer->GetComponentScale();
	}

	{
		WeaponsPanelRenderer = CreateDefaultSubObject<USpriteRenderer>();
		WeaponsPanelRenderer->SetSprite("InGameUI_LevelUpWeapons.png");
		WeaponsPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 2);
		WeaponsPanelRenderer->SetSpriteScale(1.0f);
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
		MainPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
		WeaponsPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 2);

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
	MainPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
	WeaponsPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 2);
}