#pragma once
#include "Weapon.h"

class Whip : public AWeapon
{
public:
	Whip();
	~Whip();

	Whip(const Whip& _Other) = delete;
	Whip(Whip&& _Other) noexcept = delete;
	Whip& operator=(const Whip& _Other) = delete;
	Whip& operator=(Whip&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Action() override;

	void FadeIn();
	void FadeOut();

protected:

private:
	float FadeValue = 0.0f;
	float FadeDir = 1.0f;
	void FadeChange();
};

