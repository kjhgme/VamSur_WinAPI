#pragma once
#include "Weapon.h"
class Spellbinder : public AWeapon
{
public:
	Spellbinder();
	~Spellbinder();

	Spellbinder(const Spellbinder& _Other) = delete;
	Spellbinder(Spellbinder&& _Other) noexcept = delete;
	Spellbinder& operator=(const Spellbinder& _Other) = delete;
	Spellbinder& operator=(Spellbinder&& _Other) noexcept = delete;

protected:

private:

};

