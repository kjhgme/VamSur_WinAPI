#include "PreCompile.h"
#include "WeaponManager.h"
#include "ContentsEnum.h"

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
		AddWeapon(EWeaponType::Whip);
	}
	else if (AInGameMode::Player->PlayerStatus.Name == "Imelda")
	{
		AddWeapon(EWeaponType::MagicWand);
	}

	Weapons[0]->Action();
}

void AWeaponManager::SetIconPos(AWeapon* _Weapon)
{
	USpriteRenderer* Icon = _Weapon->GetIconSpriteRenderer();
	Icon = CreateDefaultSubObject<USpriteRenderer>();
	Icon->SetOrder(ERenderOrder::UI);

	switch (_Weapon->WeaponType)
	{
	case EWeaponType::Whip:
		Icon->SetSprite("WeaponIcon", 0);
		break;
	case EWeaponType::MagicWand:
		Icon->SetSprite("WeaponIcon", 2);
		break;
	case EWeaponType::Knife:
		break;
	case EWeaponType::Axe:
		break;
	case EWeaponType::KingBible:
		break;
	default:
		return;
	}

	for (int i = 0; i < 6; ++i) {
		if (Weapons[i]->WeaponType == _Weapon->WeaponType)
		{
			Icon->SetComponentLocation({ -620.0f + (i * 35.0f), -350.0f});

			break;
		}
	}

	Icon->SetSpriteScale(1.0f);
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

			SetIconPos(Weapons[i]);
			Weapons[i]->Action();

			return; 
		}
	}
}

