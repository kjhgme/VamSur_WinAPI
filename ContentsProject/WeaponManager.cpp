#include "PreCompile.h"
#include "WeaponManager.h"

#include "InGameMode.h"
#include "Weapon.h"
#include "Whip.h"
#include "MagicWand.h"
#include "Knife.h"
#include "Axe.h"
#include "KingBible.h"

void AWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	InitWeapon();

}

void AWeaponManager::InitWeapon()
{
	if (AInGameMode::Player->PlayerStatus.Name == "Antonio")
	{
		Weapons[0] = GetWorld()->SpawnActor<Whip>();
	}
	else if (AInGameMode::Player->PlayerStatus.Name == "Imelda")
	{
		Weapons[0] = GetWorld()->SpawnActor<MagicWand>();
	}

	Weapons[0]->Action();
}

void AWeaponManager::ChangeDir()
{
	for (int i = 0; i < 6; ++i) {
		if (Weapons[i] == nullptr)
			break;

		Weapons[i]->ChangeHeadDir();
	}
}

