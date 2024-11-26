#pragma once
#include "Weapon.h"
class Garlic : public AWeapon
{
public:
	Garlic();
	~Garlic();

	Garlic(const Garlic& _Other) = delete;
	Garlic(Garlic&& _Other) noexcept = delete;
	Garlic& operator=(const Garlic& _Other) = delete;
	Garlic& operator=(Garlic&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision() override;
	void Action() override;
	void LevelUp() override;

	void Attack();
protected:

private:
	float FadeValue = 1.0f;
	float FadeDir = -1.0f;
	void FadeChange();
};

