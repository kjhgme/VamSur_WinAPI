#include "PreCompile.h"
#include "WeaponManager.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/EngineAPICore.h>
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

std::vector<std::pair<EWeaponType, WeaponLevelData>> AWeaponManager::GetRandWeapons()
{	
	UEngineRandom RandomGenerator;

	// int WeaponCount = static_cast<int>(EPassiveWeaponType::TotalCount);
	int Count = static_cast<int>(EWeaponType::WeaponCount);
	std::vector<int> WeaponIndices;
	for (int i = 0; i < Count; ++i) {
		WeaponIndices.push_back(i);
	}

	std::vector<int> RandomSelections;
	for (int i = 0; i < 3; ++i) {
		int RandomIndex = RandomGenerator.RandomInt(0, static_cast<int>(WeaponIndices.size()) - 1);
		RandomSelections.push_back(WeaponIndices[RandomIndex]);
		WeaponIndices.erase(WeaponIndices.begin() + RandomIndex);
	}

	// TODO
	// 무기의 레벨이 최대치면 다른 무기
	// 레벨이 최대치가 아닌 무기가 없으면 골드
	std::vector<std::pair<EWeaponType, WeaponLevelData>> RandWeapons;
		
	for (int i = 0; i < RandomSelections.size(); ++i)
	{
		int SelectedIndex = RandomSelections[i];
		EWeaponType SelectedType = static_cast<EWeaponType>(SelectedIndex);

		if (SelectedIndex < static_cast<int>(EWeaponType::WeaponCount))
		{
			for (int j = 0; j < 6; ++j)
			{
				if (Weapons[j] == nullptr)
				{
					RandWeapons.emplace_back(SelectedType, Weapons[0]->LevelDescriptions[7]);
					break;
				}

				// 가지고 있을 때
				if (Weapons[j]->WeaponType == SelectedType)
				{
					RandWeapons.emplace_back(SelectedType, Weapons[j]->LevelDescriptions[Weapons[j]->Level]);
					break;
				}
			}
		}
		else if(SelectedIndex < static_cast<int>(EPassiveWeaponType::TotalCount))
		{	// 패시브

		}
		else {
			// 골드
		}
	}


	return RandWeapons;
}

void AWeaponManager::SetIconPos(AWeapon* _Weapon)
{
	USpriteRenderer* Icon = _Weapon->GetIconSpriteRenderer();
	Icon = CreateDefaultSubObject<USpriteRenderer>();
	Icon->SetOrder(ERenderOrder::UI);
	Icon->SetCameraEffect(false);

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
			Icon->SetComponentLocation({ 20.0f + (i * 32.0f), 50.0f });
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

