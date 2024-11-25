#include "PreCompile.h"
#include "WeaponManager.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/EngineAPICore.h>
#include "WeaponsLevelDescriptions.h"
#include "InGameMode.h"
#include "Whip.h"
#include "MagicWand.h"
#include "Knife.h"
#include "FireWand.h"
#include "KingBible.h"
#include "Garlic.h"
#include "HollowHeart.h"
#include "EmptyTome.h"
#include "Bracer.h"
#include "Spinach.h"
#include "Spellbinder.h"
#include "Pummarola.h"

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

	for (int i = 0; i < static_cast<int>(EWeaponType::TotalCount); ++i)
	{
		AvailableWeaponTypes.push_back(i);
	}
}

std::vector<std::pair<EWeaponType, WeaponLevelData>> AWeaponManager::GetRandWeapons()
{	
	UEngineRandom RandomGenerator;

	std::vector<int> SellectableWeapons;
	std::vector<int> RandomSelections;
	std::vector<std::pair<EWeaponType, WeaponLevelData>> RandWeapons;

	SellectableWeapons = AvailableWeaponTypes;

	int Count = UEngineMath::Clamp(static_cast<int>(AvailableWeaponTypes.size()), 0, 3);

	for (int i = 0; i < Count; ++i) {
		int RandomIndex = RandomGenerator.RandomInt(0, static_cast<int>(SellectableWeapons.size() - 1));
		RandomSelections.push_back(SellectableWeapons[RandomIndex]);
		SellectableWeapons.erase(SellectableWeapons.begin() + RandomIndex);
	}
			
	for (int i = 0; i < RandomSelections.size(); ++i)
	{
		int SelectedIndex = RandomSelections[i];
		EWeaponType SelectedType = static_cast<EWeaponType>(SelectedIndex);

		if (SelectedIndex < static_cast<int>(EWeaponType::TotalCount) / 2)
		{
			for (int j = 0; j < 6; ++j)
			{
				// 가지고 있지 않을때
				if (Weapons[j] == nullptr)
				{
					std::string Description = WeaponLevelDescriptions::GetLevel1Description(SelectedType);
					RandWeapons.emplace_back(SelectedType, WeaponLevelData{ 1, Description });
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
		else if(static_cast<int>(EWeaponType::TotalCount) / 2 <= SelectedIndex)
		{	// 패시브
			for (int j = 6; j < 12; ++j)
			{
				// 가지고 있지 않을때
				if (Weapons[j] == nullptr)
				{
					std::string Description = WeaponLevelDescriptions::GetLevel1Description(SelectedType);
					RandWeapons.emplace_back(SelectedType, WeaponLevelData{ 1, Description });
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
	}

	while (true)
	{
		if (RandWeapons.size() >= 3)
			break;
		if (RandomGenerator.RandomInt(0, 1) == 1)
		{
			std::string Description = WeaponLevelDescriptions::GetLevel1Description(EWeaponType::BigCoinBag);
			RandWeapons.emplace_back(EWeaponType::BigCoinBag, WeaponLevelData{ 1, Description });
		}
		else 
		{
			std::string Description = WeaponLevelDescriptions::GetLevel1Description(EWeaponType::FloorChicken);
			RandWeapons.emplace_back(EWeaponType::FloorChicken, WeaponLevelData{ 1, Description });
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

	if (static_cast<int>(_Weapon->WeaponType) < static_cast<int>(EWeaponType::TotalCount) / 2)
	{
		switch (_Weapon->WeaponType)
		{
		case EWeaponType::Whip:
			Icon->SetSprite("WeaponIcon", 0);
			break;
		case EWeaponType::MagicWand:
			Icon->SetSprite("WeaponIcon", 2);
			break;
		case EWeaponType::Knife:
			Icon->SetSprite("WeaponIcon", 4);
			break;
		case EWeaponType::FireWand:
			Icon->SetSprite("WeaponIcon", 6);
			break;
		case EWeaponType::KingBible:
			Icon->SetSprite("WeaponIcon", 8);
			break;
		case EWeaponType::Garlic:
			Icon->SetSprite("WeaponIcon", 10);
			break;
		default:
			return;
		}

		for (int i = 0; i < 6; ++i) {
			if (Weapons[i]->WeaponType == _Weapon->WeaponType)
			{
				Icon->SetComponentLocation({ 20.0f + (i * 32.0f), 51.0f });
				break;
			}
		}
	}
	else
	{
		switch (_Weapon->WeaponType)
		{
		case EWeaponType::HollowHeart:
			Icon->SetSprite("WeaponIcon", 12);
			break;
		case EWeaponType::EmptyTome:
			Icon->SetSprite("WeaponIcon", 13);
			break;
		case EWeaponType::Bracer:
			Icon->SetSprite("WeaponIcon", 14);
			break;
		case EWeaponType::Spinach:
			Icon->SetSprite("WeaponIcon", 15);
			break;
		case EWeaponType::Spellbinder:
			Icon->SetSprite("WeaponIcon", 16);
			break;
		case EWeaponType::Pummarola:
			Icon->SetSprite("WeaponIcon", 17);
			break;
		default:
			return;
		}

		for (int i = 6; i < 12; ++i) {
			if (Weapons[i]->WeaponType == _Weapon->WeaponType)
			{
				Icon->SetComponentLocation({ 20.0f + ((i-6) * 32.0f), 83.0f });
				break;
			}
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
	// 무기만
	if (static_cast<int>(_Type) < static_cast<int>(EWeaponType::TotalCount) / 2)
	{
		for (int i = 0; i < 6; ++i)
		{
			if (Weapons[i] != nullptr && Weapons[i]->WeaponType == _Type)
			{
				Weapons[i]->LevelUp();

				if (Weapons[i]->Level == 8)
				{
					for (int j = 0; j < AvailableWeaponTypes.size(); ++j)
					{
						if (AvailableWeaponTypes[j] == static_cast<int>(Weapons[i]->WeaponType))
						{
							AvailableWeaponTypes.erase(AvailableWeaponTypes.begin() + j);
							break;
						}
					}					
				}
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
				case EWeaponType::FireWand:
					Weapons[i] = GetWorld()->SpawnActor<FireWand>();
					break;
				case EWeaponType::KingBible:
					Weapons[i] = GetWorld()->SpawnActor<KingBible>();
					break;
				case EWeaponType::Garlic:
					Weapons[i] = GetWorld()->SpawnActor<Garlic>();
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
	// 패시브 무기
	else
	{
		for (int i = 6; i < 12; ++i)
		{
			if (Weapons[i] != nullptr && Weapons[i]->WeaponType == _Type)
			{
				Weapons[i]->LevelUp();

				if (Weapons[i]->Level == 5)
				{
					for (int j = 0; j < AvailableWeaponTypes.size(); ++j)
					{
						if (AvailableWeaponTypes[j] == static_cast<int>(Weapons[i]->WeaponType))
						{
							AvailableWeaponTypes.erase(AvailableWeaponTypes.begin() + j);
							break;
						}
					}
				}
				return;
			}
		}
		// 같은게 없다면
		for (int i = 6; i < 12; ++i) {
			if (Weapons[i] == nullptr)
			{
				switch (_Type)
				{
				case EWeaponType::HollowHeart:
					Weapons[i] = GetWorld()->SpawnActor<HollowHeart>();
					break;
				case EWeaponType::EmptyTome:
					Weapons[i] = GetWorld()->SpawnActor<EmptyTome>();
					break;
				case EWeaponType::Bracer:
					Weapons[i] = GetWorld()->SpawnActor<Bracer>();
					break;
				case EWeaponType::Spinach:
					Weapons[i] = GetWorld()->SpawnActor<Spinach>();
					break;
				case EWeaponType::Spellbinder:
					Weapons[i] = GetWorld()->SpawnActor<Spellbinder>();
					break;
				case EWeaponType::Pummarola:
					Weapons[i] = GetWorld()->SpawnActor<Pummarola>();
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
}

