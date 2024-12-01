#pragma once

#include "Weapon.h"
class AWeaponManager : public AActor
{
public:
	AWeaponManager() {};
	~AWeaponManager() {};

	AWeaponManager(const AWeaponManager& _Other) = delete;
	AWeaponManager(AWeaponManager&& _Other) noexcept = delete;
	AWeaponManager& operator=(const AWeaponManager& _Other) = delete;
	AWeaponManager& operator=(AWeaponManager&& _Other) noexcept = delete;

	void BeginPlay() override;

	// InitFunction
	void InitWeapon();

	// GetFunction
	std::vector<std::pair<EWeaponType, WeaponLevelData>> GetRandWeapons();

	std::vector<int> GetLeve8Weapons()
	{
		return Level8Weapons;
	}

	std::vector<int> GetAvailableWeaponTypes()
	{
		return AvailableWeaponTypes;
	}

	AWeapon* GetWeapon(int _Num)
	{
		return Weapons[_Num];
	}

	AWeapon* GetWeaponFromType(int _Num)
	{
		for (int i = 0; i < 12; ++i)
		{
			if (static_cast<int>(Weapons[i]->WeaponType) == _Num)
			{
				return Weapons[i];
			}
		}

		return nullptr;
	}

	// SetFunction
	void SetIconPos(AWeapon* _Weapon);

	// Function
	void ChangeDir();
	void AddWeapon(EWeaponType _Type);

	void RevolutionWeapon(int _Num)
	{
		Level8Weapons.erase(Level8Weapons.begin() + _Num);
	}
	
protected:

private:
	class AWeapon* Weapons[12]{};
	std::vector<int> AvailableWeaponTypes;
	std::vector<int> Level8Weapons;
};

