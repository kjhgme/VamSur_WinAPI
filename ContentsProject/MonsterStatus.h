#pragma once
#include <string>

struct MonsterStatus {
	std::string Name = "None";
	int Health = -1;
	int Power = -1;
	int Speed = -1;
	float KnockBack = -1;
	int KBMax = -1;
	int XP = -1;

    MonsterStatus() {};

    MonsterStatus(std::string name, int health, int power, int speed, int knockBack, int kbMax, int xp)
        : Name(name), Health(health), Power(power), Speed(speed), KnockBack(knockBack), KBMax(kbMax), XP(xp){}
};
// Name, Health, Armor, Might, Speed
inline const MonsterStatus Bat1Status("Bat1", 1, 5, 140, 1, 3, 1);
inline const MonsterStatus Ghoul1Status("Ghoul1", 10, 10, 100, 0.8, 3, 1);
