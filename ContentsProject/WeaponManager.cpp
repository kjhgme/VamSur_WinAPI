#include "PreCompile.h"
#include "WeaponManager.h"

#include "InGameMode.h"
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

void AWeaponManager::AddWeapon(EWeaponType _Type)
{
	for (int i = 0; i < 6; ++i)
	{
		if (Weapons[i] != nullptr && Weapons[i]->WeaponType == _Type)
		{
			Weapons[i]->LevelUp();
			return;
		}
	}
	// 같은게 없다면
	for (int i = 0; i < 6; ++i) {
		if (Weapons[i] == nullptr)
		{
			switch (_Type)
			{
			case EWeaponType::Whip:
				Weapons[i] = GetWorld()->SpawnActor<Whip>();
				break;
			case EWeaponType::MagicWand:
				Weapons[i] = GetWorld()->SpawnActor<MagicWand>();
				break;
			case EWeaponType::Knife:
				Weapons[i] = GetWorld()->SpawnActor<Knife>();
				break;
			case EWeaponType::Axe:
				Weapons[i] = GetWorld()->SpawnActor<Axe>();
				break;
			case EWeaponType::KingBible:
				Weapons[i] = GetWorld()->SpawnActor<KingBible>();
				break;
			default:
				return;
			}
			
			Weapons[i]->Action();

			return;  // 무기를 추가했으면 함수를 종료
		}
	}
}

