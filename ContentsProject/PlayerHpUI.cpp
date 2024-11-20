#include "PreCompile.h"
#include "PlayerHpUI.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

PlayerHpUI::PlayerHpUI()
{
	{
		HpBarRenderer = CreateDefaultSubObject<USpriteRenderer>();
		HpBarRenderer->SetSprite("InGameUI_HpBar.png");
		HpBarRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));

		HpBarRenderer->SetSpriteScale(1.0f);

		// HpBarRenderer->SetComponentScale({ 0.0f, 20.0f });
		// HpBarRenderer->SetComponentLocation({ -(MaxExp / 2.0f), 0.0f });
	}
	{
		HpBarFillRenderer = CreateDefaultSubObject<USpriteRenderer>();
		HpBarFillRenderer->SetSprite("InGameUI_HpBarFill.png");
		HpBarFillRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		HpBarFillRenderer->SetPivotType(PivotType::LeftTop);
		// HpBarFillRenderer->SetComponentScale({ 0.0f, 20.0f });
		// HpBarFillRenderer->SetComponentLocation({ -(MaxExp / 2.0f), 0.0f });
	}
}

PlayerHpUI::~PlayerHpUI()
{
}

void PlayerHpUI::BeginPlay()
{
	Super::BeginPlay();
}

void PlayerHpUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D Pos = AInGameMode::Player->GetActorLocation();
	Pos.Y += 45.0f;

	SetActorLocation(Pos);
}
