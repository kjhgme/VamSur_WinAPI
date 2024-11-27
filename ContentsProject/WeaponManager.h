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

	// SetFunction
	void SetIconPos(AWeapon* _Weapon);

	// Function
	void ChangeDir();
	void AddWeapon(EWeaponType _Type);
	
protected:

private:
	class AWeapon* Weapons[12]{};
	std::vector<int> AvailableWeaponTypes;
	std::vector<int> Level8Weapons;
};

