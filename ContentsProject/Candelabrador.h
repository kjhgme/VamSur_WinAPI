#pragma once
#include "Weapon.h"
class Candelabrador : public AWeapon
{
public:
	Candelabrador();
	~Candelabrador();

	Candelabrador(const Candelabrador& _Other) = delete;
	Candelabrador(Candelabrador&& _Other) noexcept = delete;
	Candelabrador& operator=(const Candelabrador& _Other) = delete;
	Candelabrador& operator=(Candelabrador&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Action() override;

protected:

private:

};

