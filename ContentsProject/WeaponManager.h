#pragma once
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

	void ChangeDir();

protected:

private:
	class AWeapon* Weapons[6]{};
	class AWeapon* PassiveWeapons[6]{};
};

