#pragma once
#include <string>

struct CharacterStatus {
    std::string Name = "Imelda";
    int Health = 120;
    int Armor = 1;
    int Might = 0;
    int Speed = 160;

    CharacterStatus() {};

    CharacterStatus(std::string name, int health, int armor, int might, int speed)
        : Name(name), Health(health), Armor(armor), Might(might), Speed(speed) {}
};
                                // Name, Health, Armor, Might, Speed
inline const CharacterStatus AntonioStatus("Antonio", 120, 1, 0, 160);
inline const CharacterStatus ImeldaStatus("Imelda", 120, 1, 0, 160);