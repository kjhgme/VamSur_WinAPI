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

	FVector2D CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle);

protected:

private:
	float MoveSpeed = 150.0f;
	float CurAngle{};

	FVector2D Pos{};
	std::vector<USpriteRenderer*> BibleRenderers;

	void AddBible();
};

