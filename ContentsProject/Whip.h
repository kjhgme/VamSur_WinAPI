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

	void InitCollision() override;
	void Action() override;
	void LevelUp() override;
	void ChangeHeadDir() override;

	void Attack();

protected:

private:
	float FadeValue = 1.0f;
	float SecondFadeValue = 1.0f;
	float FadeDir = -1.0f;
	FVector2D Scale{};
	class USpriteRenderer* SecondRenderer = nullptr;

	void FadeOut();
	void AddWhip();
};

