#include "PreCompile.h"
#include "ExpBarUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>

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
	Super::BeginPlay();

	LevelText = GetWorld()->SpawnActor<ATextBox>();
	LevelText->InitOrder(static_cast<int>(ERenderOrder::UI) + 1);
	LevelText->SetTextScale(12);
	LevelText->SetAlignLeft(false);
	LevelText->SetText("LV " + std::to_string(PlayerLevel));
	LevelText->SetPos({ 1260.0f, 13.0f });
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

void ExpBarUI::SetPlayerLevel()
{
	PlayerLevel++;
	LevelText->SetText("LV " + std::to_string(PlayerLevel));
}
