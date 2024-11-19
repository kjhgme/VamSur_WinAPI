#pragma once
#include "Weapon.h"

class Knife : AWeapon
{
public:
	Knife();
	~Knife();

	Knife(const Knife& _Other) = delete;
	Knife(Knife&& _Other) noexcept = delete;
	Knife& operator=(const Knife& _Other) = delete;
	Knife& operator=(Knife&& _Other) noexcept = delete;

protected:

private:

};

