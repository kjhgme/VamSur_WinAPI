#include "PreCompile.h"
#include "MagicWand.h"

MagicWand::MagicWand()
{
	WeaponName = "MagicWand";

	LevelDescriptions = {
		{1, "Fires at the nearest enemy."},
		{2, "Fires 1 more projectile."},
		{3, "Cooldown reduced by 0.2 seconds."},
		{4, "Fires 1 more projectile."},
		{5, "Base Damage up by 10."},
		{6, "Fires 1 more projectile."},
		{7, "Passes through 1 more enemy."},
		{8, "Base Damage up by 10."},
	};
}

MagicWand::~MagicWand()
{
}
