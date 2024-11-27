#include "PreCompile.h"
#include "InGameUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

#include "WeaponSlotsUI.h"
#include "TimeUI.h"

ExpBarUI* AInGameUI::ExpBar;
LevelUpUI* AInGameUI::LevelUpPanel;
KillAndGoldUI* AInGameUI::KillAndGold;

AInGameUI::AInGameUI()
{
}

AInGameUI::~AInGameUI()
{
}

void AInGameUI::BeginPlay()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.Half() });

	WeaponSlotsUI* WeaponSlots = GetWorld()->SpawnActor<WeaponSlotsUI>();
	ATimeUI* TimeUI = GetWorld()->SpawnActor<ATimeUI>();

	ExpBar = GetWorld()->SpawnActor<ExpBarUI>();
	LevelUpPanel = GetWorld()->SpawnActor<LevelUpUI>();
	KillAndGold = GetWorld()->SpawnActor<KillAndGoldUI>();
}

void AInGameUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
