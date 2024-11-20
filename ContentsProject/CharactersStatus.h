#pragma once
#include <string>

struct CharacterStatus {
    std::string Name = "Imelda";
    float Hp = 100.0f;
    float MaxHp = 100.0f;
    int Armor = 1;
    int Might = 0;
    float Speed = 160.0f;
    int Level = 1;
    float MaxExp = 5.0f;
    float Exp = 0.0f;

    CharacterStatus() {};

    CharacterStatus(std::string name, float hp, int armor, int might, float speed, int level = 1, float MaxExp = 0.0f, float Exp = 0.0f)
        : Name(name), Hp(hp), MaxHp(hp), Armor(armor), Might(might), Speed(speed), Level(level) {}
};
                                // Name, Health, Armor, Might, Speed
inline const CharacterStatus AntonioStatus("Antonio", 120.0f, 1, 0, 240.0f);
inline const CharacterStatus ImeldaStatus("Imelda", 120.0f, 1, 0, 160.0f);