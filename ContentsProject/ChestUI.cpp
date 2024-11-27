#include "PreCompile.h"
#include "ChestUI.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

UEngineRandom ChestRandomGenerator;

ChestUI::ChestUI()
{
	UEngineAPICore::GetCore()->GetTimer().ToggleTime();
	
	{
		PanelRenderer = CreateDefaultSubObject<USpriteRenderer>();
		PanelRenderer->SetSprite("InGameUI_BlankPanel.png");
		PanelRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
		PanelRenderer->SetSpriteScale(1.0f);
	}
	{
		ChestRenderer = CreateDefaultSubObject<USpriteRenderer>();
		ChestRenderer->SetSprite("Chest", 0);
		ChestRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 2);
		ChestRenderer->SetSpriteScale(1.0f);
		ChestRenderer->CreateAnimation("Chest_Idle", "Chest", 0, 7, 0.1f, false);
	}

	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	FVector2D ChestUIPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
	ChestUIPos.Y = ChestUIPos.Y - WindowSize.Half().Y + PanelRenderer->GetComponentScale().Half().Y;

	SetActorLocation(ChestUIPos);

	ChestRenderer->SetComponentLocation({ 0.0f, 150.0f });
	ChestRenderer->ChangeAnimation("Chest_Idle");

	float t = UEngineAPICore::GetCore()->GetTimer().GetDeltaTime();
	float it = UEngineAPICore::GetCore()->GetTimer().GetIndependentDeltaTime();

	int a = 0;
}

ChestUI::~ChestUI()
{
}

void ChestUI::OpenChest()
{
	if (3.0f >= ChestRandomGenerator.Randomfloat(0.0f, 100.0f))
	{
		
	}
	else if (10.0f >= ChestRandomGenerator.Randomfloat(0.0f, 100.0f))
	{

	}
	else {

	}
}

void ChestUI::GetWeapon()
{
}
