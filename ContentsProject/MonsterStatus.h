#pragma once
#include <string>

struct MonsterStatus {
	std::string Name = "None";
	int Health = -1;
	int Power = -1;
	int Speed = -1;
	float KnockBack = -1;
	int KBMax = -1;
	float XP = -1;

    MonsterStatus() {};

    MonsterStatus(std::string name, int health, int power, int speed, int knockBack, int kbMax, float xp)
        : Name(name), Health(health), Power(power), Speed(speed), KnockBack(knockBack), KBMax(kbMax), XP(xp){}
};

								// Name, Health, Armor, Might, Speed
inline const MonsterStatus Bat1Status("Bat1", 1, 5, 140, 1, 3, 1);
inline const MonsterStatus Bat2Status("Bat2", 5, 5, 140, 1, 3, 1);
inline const MonsterStatus Bat3Status("Bat3", 5, 5, 140, 1, 3, 1);
inline const MonsterStatus Ghoul1Status("Ghoul1", 10, 10, 100, 0.8, 3, 1);
inline const MonsterStatus Ghoul2Status("Ghoul2", 10, 10, 100, 0.8, 3, 1);
inline const MonsterStatus Ghoul3Status("Ghoul3", 10, 10, 100, 0.8, 3, 1);
inline const MonsterStatus Skeleton1Status("Skeleton1", 15, 10, 100, 1, 3, 2);
inline const MonsterStatus Ghost1Status("Ghost1", 10, 5, 200, 0, 3, 1.5);
inline const MonsterStatus Mudman1Status("Mudman1", 70, 10, 100, 0.3, 3, 2.5);
inline const MonsterStatus Mudman2Status("Mudman2", 150, 10, 100, 0.3, 3, 2.5);
inline const MonsterStatus GiantBatStatus("GiantBat", 270, 10, 140, 0.1, 3, 2.5);
inline const MonsterStatus WerewolfStatus("Werewolf", 180, 14, 130, 0.8, 3, 2);
inline const MonsterStatus MantichanaStatus("Mantichana", 500, 10, 80, 0, 3, 3);
inline const MonsterStatus BigMummyStatus("BigMummy", 500, 20, 80, 0, 3, 3);
inline const MonsterStatus VenusStatus("Venus", 500, 20, 80, 0, 3, 3);

inline const MonsterStatus GlowingBatStatus("GlowingBat", 50, 10, 140, 1, 3, 30);
inline const MonsterStatus SilverBatStatus("SilverBat", 50, 10, 140, 1, 3, 30);
inline const MonsterStatus FlowerWallStatus("FlowerWall", 30, 1, 20,1, 3, 2);
inline const MonsterStatus MantichanaLordStatus("MantichanaLord", 150, 20, 160, 0, 1, 50);
inline const MonsterStatus WerewolfLordStatus("WerewolfLord", 200, 20, 130, 0.1, 1, 2);
inline const MonsterStatus MummyLordStatus("MummyLord", 250, 20, 80, 0, 1, 25);
inline const MonsterStatus VenusLordStatus("VenusLord", 150, 30, 160, 0, 1, 50);
inline const MonsterStatus TheReaperStatus("TheReaper", 655350, 65535, 140, 1200, -0.5, 0);
