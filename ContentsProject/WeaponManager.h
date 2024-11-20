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

	void InitWeapon();

	void SetIconPos(AWeapon* _Weapon);

	void ChangeDir();
	void AddWeapon(EWeaponType _Type);
	
protected:

private:
	class AWeapon* Weapons[6]{};
	class AWeapon* PassiveWeapons[6]{};
};

