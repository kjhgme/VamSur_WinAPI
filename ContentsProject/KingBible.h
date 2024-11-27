#pragma once
#include "Weapon.h"
class KingBible : public AWeapon
{
public:
	KingBible();
	~KingBible();

	KingBible(const KingBible& _Other) = delete;
	KingBible(KingBible&& _Other) noexcept = delete;
	KingBible& operator=(const KingBible& _Other) = delete;
	KingBible& operator=(KingBible&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision(int _Num);
	void Action() override;
	void LevelUp() override;

	void Attack();
	void FadeOut();
	void ChangeDuration();

	FVector2D CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle);

protected:

private:
	float CurAngle{};
	float FadeValue = 0.0f;
	float FadeDir = 1.0f;

	bool bStartAttack = false;
	bool bStartFadeOut = false;

	FVector2D Pos{};
	std::vector<USpriteRenderer*> BibleRenderers;

	void AddBible();
};

