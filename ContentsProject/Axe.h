#pragma once
#include "Weapon.h"
class Axe : public AWeapon
{
public:
	Axe();
	~Axe();

	Axe(const Axe& _Other) = delete;
	Axe(Axe&& _Other) noexcept = delete;
	Axe& operator=(const Axe& _Other) = delete;
	Axe& operator=(Axe&& _Other) noexcept = delete;

protected:

private:

};

