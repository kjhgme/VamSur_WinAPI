#pragma once
#include "Weapon.h"

class Pummarola : public AWeapon
{
public:
	Pummarola();
	~Pummarola();

	Pummarola(const Pummarola& _Other) = delete;
	Pummarola(Pummarola&& _Other) noexcept = delete;
	Pummarola& operator=(const Pummarola& _Other) = delete;
	Pummarola& operator=(Pummarola&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Action() override;

protected:

private:

};

