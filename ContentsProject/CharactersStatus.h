#pragma once
#include <string>

struct CharacterStatus {
    std::string Name = "Imelda";
    int Hp = 120;
    int Armor = 1;
    int Might = 0;
    int Speed = 160;
    int Level = 1;

    CharacterStatus() {};

    CharacterStatus(std::string name, int hp, int armor, int might, int speed, int level = 1)
        : Name(name), Hp(hp), Armor(armor), Might(might), Speed(speed), Level(level) {}
};
                                // Name, Health, Armor, Might, Speed
inline const CharacterStatus AntonioStatus("Antonio", 120, 1, 0, 160);
inline const CharacterStatus ImeldaStatus("Imelda", 120, 1, 0, 160);