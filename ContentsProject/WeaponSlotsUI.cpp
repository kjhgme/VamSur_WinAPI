#include "PreCompile.h"
#include "WeaponSlotsUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

WeaponSlotsUI::WeaponSlotsUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetPos();

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("InGameUI_WeaponSlots.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);

		Scale = SpriteRenderer->GetComponentScale();
	}
}

WeaponSlotsUI::~WeaponSlotsUI()
{
}

void WeaponSlotsUI::BeginPlay()
{
}

void WeaponSlotsUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	SetPos();
}

void WeaponSlotsUI::SetPos()
{
	Pos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
	Pos.X = Pos.X - WindowSize.Half().X + 100.0f;
	Pos.Y = Pos.Y - WindowSize.Half().Y + Scale.Half().Y + 35.0f;

	SetActorLocation({ Pos });
}
