#include "PreCompile.h"
#include "ExpBarUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include "InGameMode.h"

const FVector2D LevelFillLoc{ -(1270.0f / 2.0f), 0.0f };

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
	{
		LevelFillRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LevelFillRenderer->SetSprite("InGameUI_LevelBarFill.png");
		LevelFillRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		LevelFillRenderer->SetPivotType(PivotType::Left);
		LevelFillRenderer->SetComponentLocation(LevelFillLoc);
		LevelFillRenderer->SetComponentScale({100.0f, 20.0f});
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
	LevelText->SetText("LV " + std::to_string(AInGameMode::Player->PlayerStatus.Level));
	LevelText->SetPos({ 1260.0f, 13.0f });
}

void ExpBarUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	float ExpRatio = AInGameMode::Player->PlayerStatus.Exp / AInGameMode::Player->PlayerStatus.MaxExp;
	float LevelFillRatio = 2 * ExpRatio * UEngineMath::Abs(LevelFillLoc.X);
	LevelFillRenderer->SetComponentScale({ LevelFillRatio, 20.0f });
	
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
	LevelText->Destroy(); 
	LevelText = GetWorld()->SpawnActor<ATextBox>();
	LevelText->InitOrder(static_cast<int>(ERenderOrder::UI) + 1);
	LevelText->SetTextScale(12);
	LevelText->SetAlignLeft(false);
	LevelText->SetPos({ 1260.0f, 13.0f });
	LevelText->SetText("LV " + std::to_string(AInGameMode::Player->PlayerStatus.Level));
}
