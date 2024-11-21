#pragma once
#include <string>
#include "Weapon.h" // EWeaponType enum 포함

class WeaponLevelDescriptions
{
public:
    static std::string GetLevel1Description(EWeaponType WeaponType)
    {        
        switch (WeaponType)
        {
        case EWeaponType::Whip:
            return "Attacks horizontally,\npasses through enemies.";
        case EWeaponType::MagicWand:
            return "Fires at the nearest enemy.";
        case EWeaponType::Knife:
            return "Fires quickly in the faced\ndirection.";
        case EWeaponType::Axe:
            return "High damage, high Area scaling.";
        case EWeaponType::KingBible:
            return "Orbits around the player.";
        default:
            return "Unknown weapon.";
        }        
    };
};