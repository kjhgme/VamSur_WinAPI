#pragma once
#include "Monster.h"

#include <string>

class Bat1 : public AMonster
{
public:
	Bat1();
	~Bat1();

	Bat1(const Bat1& _Other) = delete;
	Bat1(Bat1&& _Other) noexcept = delete;
	Bat1& operator=(const Bat1& _Other) = delete;
	Bat1& operator=(Bat1&& _Other) noexcept = delete;

	void InitSprite() override;
	void InitMonsterStatus() override;

protected:

private:
	struct BatS
	{
		std::string Name = "Bat1";
		const int Health = 1;
		const int Power = 5;
		const int Speed = 140;
		const int KnockBack = 1;
		const int KBMax = 3;
		const int XP = 1;
	} Bat1Status;
};

