#pragma once
#include <string>

struct MonsterStatus {
	std::string Name = "None";
	int Hp = -1;
	int AttPower = -1;
	int Speed = -1;
	float KnockBack = -1.0f;
	float KBMax = -1.0f;
	float XP = -1;
	bool HaveSkill = false;

    MonsterStatus() {};

    MonsterStatus(std::string name, int hp, int power, int speed, float knockBack, float kbMax, float xp, bool haveSkill = false)
        : Name(name), Hp(hp), AttPower(power), Speed(speed), KnockBack(knockBack), KBMax(kbMax), XP(xp), HaveSkill(haveSkill){}
};

inline const MonsterStatus Bat1Status("Bat1", 1, 5, 140, 1.0f, 3.0f, 1.0f);
inline const MonsterStatus Bat2Status("Bat2", 5, 5, 140, 1.0f, 3.0f, 1.0f);
inline const MonsterStatus Bat3Status("Bat3", 5, 5, 140, 1.0f, 3.0f, 1.0f);
inline const MonsterStatus Ghoul1Status("Ghoul1", 10, 10, 100, 0.8f, 3.0f, 1.0f);
inline const MonsterStatus Ghoul2Status("Ghoul2", 10, 10, 100, 0.8f, 3.0f, 1.0f);
inline const MonsterStatus Ghoul3Status("Ghoul3", 10, 10, 100, 0.8f, 3.0f, 1.0f);
inline const MonsterStatus Skeleton1Status("Skeleton1", 15, 10, 100, 1.0f, 3.0f, 2.0f);
inline const MonsterStatus Ghost1Status("Ghost1", 10, 5, 200, 0.0f, 3.0f, 1.5f);
inline const MonsterStatus Mudman1Status("Mudman1", 70, 10, 100, 0.3f, 3.0f, 2.5f);
inline const MonsterStatus Mudman2Status("Mudman2", 150, 10, 100, 0.3f, 3.0f, 2.5f);
inline const MonsterStatus GiantBatStatus("GiantBat", 270, 10, 140, 0.1f, 3.0f, 2.5f);
inline const MonsterStatus WerewolfStatus("Werewolf", 180, 14, 130, 0.8f, 3.0f, 2.0f);
inline const MonsterStatus MantichanaStatus("Mantichana", 500, 10, 80, 0.0f, 3.0f, 3.0f);
inline const MonsterStatus BigMummyStatus("BigMummy", 500, 20, 80, 0.0f, 3.0f, 3.0f);
inline const MonsterStatus VenusStatus("Venus", 500, 20, 80, 0.0f, 3.0f, 3.0f);

inline const MonsterStatus GlowingBatStatus("GlowingBat", 50, 10, 140, 1.0f, 3.0f, 30.0f, true);
inline const MonsterStatus SilverBatStatus("SilverBat", 50, 10, 140, 1.0f, 3.0f, 30.0f, true);
inline const MonsterStatus FlowerWallStatus("FlowerWall", 30, 1, 20, 1.0f, 3.0f, 2.0f, true);
inline const MonsterStatus MantichanaLordStatus("MantichanaLord", 150, 20, 160, 0.0f, 1.0f, 50.0f, true);
inline const MonsterStatus WerewolfLordStatus("WerewolfLord", 200, 20, 130, 0.1f, 1.0f, 2.0f, true);
inline const MonsterStatus MummyLordStatus("MummyLord", 250, 20, 80, 0.0f, 1.0f, 25.0f, true);
inline const MonsterStatus VenusLordStatus("VenusLord", 150, 30, 160, 0.0f, 1.0f, 50.0f, true);
inline const MonsterStatus TheReaperStatus("TheReaper", 655350, 65535, 140, 1200, 0.0f, 0.0f, true);
