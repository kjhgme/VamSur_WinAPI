#pragma once
#include "Weapon.h"
class Bracer : public AWeapon
{
public:
	Bracer();
	~Bracer();

	Bracer(const Bracer& _Other) = delete;
	Bracer(Bracer&& _Other) noexcept = delete;
	Bracer& operator=(const Bracer& _Other) = delete;
	Bracer& operator=(Bracer&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Action() override;

	void LevelUp() override;

protected:

private:

};

