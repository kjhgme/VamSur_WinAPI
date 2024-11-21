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
        case EWeaponType::HollowHeart:
            return "Augment max health by 20%.";
        case EWeaponType::EmptyTome:
            return "Reduces weapons cooldown by 8%";
        case EWeaponType::Bracer:
            return "Increases projectiles speed by 10%";
        case EWeaponType::Candelabrador:
            return "Augments area of attacks by 10%";
        case EWeaponType::Spellbinder:
            return "Effect lasts 10% longer";
        case EWeaponType::TotalCount:
            return "It is TotalCount.\nWrong Input.";
        case EWeaponType::BigCoinBag:
            return "Adds 25 to your gold coins total.";
        case EWeaponType::FloorChicken:
            return "Restores 30 health points.";
        default:
            return "Unknown weapon.";
        }        
    };
};