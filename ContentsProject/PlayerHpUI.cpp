#include "PreCompile.h"
#include "PlayerHpUI.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

const FVector2D HpFillScale{ 68.0f, 9.0f };

PlayerHpUI::PlayerHpUI()
{
	{
		HpBarRenderer = CreateDefaultSubObject<USpriteRenderer>();
		HpBarRenderer->SetSprite("InGameUI_HpBar.png");
		HpBarRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));

		HpBarRenderer->SetSpriteScale(1.0f);
	}
	{
		HpBarFillRenderer = CreateDefaultSubObject<USpriteRenderer>();
		HpBarFillRenderer->SetSprite("InGameUI_HpBarFill.png");
		HpBarFillRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
		HpBarFillRenderer->SetPivotType(PivotType::Left);
		HpBarFillRenderer->SetComponentScale(HpFillScale);
		HpBarFillRenderer->SetComponentLocation({ -(HpFillScale.X / 2.0f), 0.0f });
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

	float CurHpfill = AInGameMode::Player->PlayerStatus.Hp / AInGameMode::Player->PlayerStatus.MaxHp;
	HpBarFillRenderer->SetComponentScale({ HpFillScale.X * CurHpfill, HpFillScale.Y });
}
