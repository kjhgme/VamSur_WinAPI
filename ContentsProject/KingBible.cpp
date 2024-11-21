#include "PreCompile.h"
#include "KingBible.h"

KingBible::KingBible()
{
	WeaponType = EWeaponType::KingBible;

	LevelDescriptions = {
		{1, "Orbits around the character."},
		{2, "Fires 1 more projectile."},
		{3, "Base Area up by 25%.\nBase Speed up by 30%."},
		{4, "Base Damage up by 10."},
		{5, "Fires 1 more projectile."},
		{6, "Base Area up by 25%.\nBase Speed up by 30%."},
		{7, "Base Damage up by 10."},
		{8, "Fires 1 more projectile."},
	};
}

KingBible::~KingBible()
{
}

void KingBible::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
}

void KingBible::Tick(float _DeltaTime)
{
}

void KingBible::InitCollision()
{
}

void KingBible::Action()
{
}
