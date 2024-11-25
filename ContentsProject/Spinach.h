#pragma once
#include "Weapon.h"
class Spinach : public AWeapon
{
public:
	Spinach();
	~Spinach();

	Spinach(const Spinach& _Other) = delete;
	Spinach(Spinach&& _Other) noexcept = delete;
	Spinach& operator=(const Spinach& _Other) = delete;
	Spinach& operator=(Spinach&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Action() override;

protected:

private:

};

