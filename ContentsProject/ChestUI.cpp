#include "PreCompile.h"
#include "ChestUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ChestUI::ChestUI()
{
	UEngineAPICore::GetCore()->GetTimer().ToggleTime();

	{
		PanelRenderer = CreateDefaultSubObject<USpriteRenderer>();
		PanelRenderer->SetSprite("InGameUI_BlankPanel.png");
		PanelRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
		PanelRenderer->SetSpriteScale(1.0f);
	}

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FVector2D ChestUIPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
	ChestUIPos.Y = ChestUIPos.Y - WindowSize.Half().Y + PanelRenderer->GetComponentScale().Half().Y;

	SetActorLocation(ChestUIPos);
}

ChestUI::~ChestUI()
{
}
