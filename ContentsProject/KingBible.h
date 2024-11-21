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

	void InitCollision() override;

	void Action() override;

protected:

private:

};

