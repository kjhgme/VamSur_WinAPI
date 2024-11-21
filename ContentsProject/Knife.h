#pragma once
#include "Weapon.h"

class Knife : public AWeapon
{
public:
	Knife();
	~Knife();

	Knife(const Knife& _Other) = delete;
	Knife(Knife&& _Other) noexcept = delete;
	Knife& operator=(const Knife& _Other) = delete;
	Knife& operator=(Knife&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision() override;

	void Action() override;

protected:

private:

};

