#include "PreCompile.h"
#include "Knife.h"

Knife::Knife()
{
	WeaponName = "Knife";

	LevelDescriptions = {
		{1, "Fires quickly in the faced direction."},
		{2, "Fires 1 more projectile."},
		{3, "Fires 1 more projectile. Base Damage up by 5."},
		{4, "Fires 1 more projectile."},
		{5, "Passes through 1 more enemy."},
		{6, "Fires 1 more projectile."},
		{7, "Fires 1 more projectile. Base Damage up by 5."},
		{8, "Passes through 1 more enemy."},
	};
}

Knife::~Knife()
{
}
