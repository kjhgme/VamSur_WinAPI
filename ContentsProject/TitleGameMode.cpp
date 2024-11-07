#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "TitleBG.h"
#include "TitleUI.h"
#include "TitleLogo.h"
#include "TitleImelda.h"
#include "TitleAntonio.h"
#include "TitleVillain.h"

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	TitleInit();
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATitleGameMode::TitleInit()
{
	ATitleBG* TitleBG = GetWorld()->SpawnActor<ATitleBG>();
	ATitleUI* TitleUI = GetWorld()->SpawnActor<ATitleUI>();
	ATitleLogo* TitleLogo = GetWorld()->SpawnActor<ATitleLogo>();
	ATitleImelda* TitleImelda = GetWorld()->SpawnActor<ATitleImelda>();
	ATitleAntonio* TitleAntonio = GetWorld()->SpawnActor<ATitleAntonio>();
	ATitleVillain* TitleVillain = GetWorld()->SpawnActor<ATitleVillain>();
}
