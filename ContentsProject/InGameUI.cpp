#include "PreCompile.h"
#include "InGameUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

#include "ExpBarUI.h"
#include "WeaponSlotsUI.h"
#include "KillAndGoldUI.h"

LevelUpUI* AInGameUI::LevelUpPanel;

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

	ExpBarUI* ExpBar = GetWorld()->SpawnActor<ExpBarUI>();
	WeaponSlotsUI* WeaponSlots = GetWorld()->SpawnActor<WeaponSlotsUI>();
	KillAndGoldUI* KillAndGold = GetWorld()->SpawnActor<KillAndGoldUI>();

	LevelUpPanel = GetWorld()->SpawnActor<LevelUpUI>();
}

void AInGameUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
