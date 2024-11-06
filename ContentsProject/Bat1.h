#pragma once
#include "Monster.h"

class Bat1 : public AMonster
{
public:
	Bat1();
	~Bat1();

	Bat1(const Bat1& _Other) = delete;
	Bat1(Bat1&& _Other) noexcept = delete;
	Bat1& operator=(const Bat1& _Other) = delete;
	Bat1& operator=(Bat1&& _Other) noexcept = delete;

	// SetFunction
	void SetSprite() override;
	void SetMonsterStatus() override;

protected:

private:
	struct BatS
	{
		int Health = 1;
		int Power = 5;
		int Speed = 140;
		int KnockBack = 1;
		int KBMax = 3;
		int XP = 1;
	} BatStatus;
};

