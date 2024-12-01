#pragma once
#include <string>

struct MonsterStatus {
	std::string Name = "None";
	float Hp = -1.0f;
	float AttPower = -1.0f;
	float Speed = -1.0f;
	float KnockBack = -1.0f;
	float KBMax = -1.0f;
	float XP = -1.0f;
	bool HaveSkill = false;

    MonsterStatus() {};

    MonsterStatus(std::string name, float hp, float power, float speed, float knockBack, float kbMax, float xp, bool haveSkill = false)
        : Name(name), Hp(hp), AttPower(power), Speed(speed), KnockBack(knockBack), KBMax(kbMax), XP(xp), HaveSkill(haveSkill){}
};

inline const MonsterStatus Bat1Status("Bat1", 1.0f, 5.0f, 140.0f, 1.0f, 3.0f, 1.0f);
inline const MonsterStatus Bat2Status("Bat2", 5.0f, 5.0f, 140.0f, 1.0f, 3.0f, 1.0f);
inline const MonsterStatus Bat3Status("Bat3", 5.0f, 5.0f, 140.0f, 1.0f, 3.0f, 1.0f);
inline const MonsterStatus Ghoul1Status("Ghoul1", 10.0f, 10.0f, 100.0f, 0.8f, 3.0f, 1.0f);
inline const MonsterStatus Ghoul2Status("Ghoul2", 10.0f, 10.0f, 100.0f, 0.8f, 3.0f, 1.0f);
inline const MonsterStatus Ghoul3Status("Ghoul3", 10.0f, 10.0f, 100.0f, 0.8f, 3.0f, 1.0f);
inline const MonsterStatus Skeleton1Status("Skeleton1", 15.0f, 10.0f, 100.0f, 1.0f, 3.0f, 2.0f);
inline const MonsterStatus Ghost1Status("Ghost", 10.0f, 5.0f, 200.0f, 0.0f, 3.0f, 1.5f);
inline const MonsterStatus Mudman1Status("Mudman1", 70.0f, 10.0f, 100.0f, 0.3f, 3.0f, 2.5f);
inline const MonsterStatus Mudman2Status("Mudman2", 150.0f, 10.0f, 100.0f, 0.3f, 3.0f, 2.5f);
inline const MonsterStatus GiantBatStatus("XLBat", 270.0f, 10.0f, 140.0f, 0.1f, 3.0f, 2.5f);
inline const MonsterStatus WerewolfStatus("Werewolf1", 180.0f, 14.0f, 130.0f, 0.8f, 3.0f, 2.0f);
inline const MonsterStatus MantichanaStatus("XLMantis", 500.0f, 10.0f, 80.0f, 0.0f, 3.0f, 3.0f);
inline const MonsterStatus BigMummyStatus("XLMummy", 500.0f, 20.0f, 80.0f, 0.0f, 3.0f, 3.0f);
inline const MonsterStatus VenusStatus("XLFlower1", 500.0f, 20.0f, 80.0f, 0.0f, 3.0f, 3.0f);

inline const MonsterStatus GlowingBatStatus("Bat4", 50.0f, 10.0f, 140.0f, 1.0f, 3.0f, 30.0f, true);
inline const MonsterStatus SilverBatStatus("Bat5", 50.0f, 10.0f, 140.0f, 1.0f, 3.0f, 30.0f, true);
inline const MonsterStatus FlowerWallStatus("Flower1", 30.0f, 1.0f, 10.0f, 1.0f, 3.0f, 2.0f, true);
inline const MonsterStatus MantichanaLordStatus("XLMantis", 150.0f, 20.0f, 160.0f, 0.0f, 1.0f, 50.0f, true);
inline const MonsterStatus WerewolfLordStatus("Werewolf1", 200.0f, 20.0f, 130.0f, 0.1f, 1.0f, 2.0f, true);
inline const MonsterStatus MummyLordStatus("XLMummy", 250.0f, 20.0f, 80.0f, 0.0f, 1.0f, 25.0f, true);
inline const MonsterStatus VenusLordStatus("XLFlower1", 150.0f, 30.0f, 160.0f, 0.0f, 1.0f, 50.0f, true);
inline const MonsterStatus TheReaperStatus("XLReaper", 655350.0f, 65535.0f, 140.0f, 1200.0f, 0.0f, 0.0f, true);
