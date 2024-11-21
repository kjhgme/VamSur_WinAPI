#include "PreCompile.h"
#include "Axe.h"

Axe::Axe()
{
	WeaponType = EWeaponType::Axe;

	LevelDescriptions = {
		{1, "High damage, high Area scaling."},
		{2, "Fires 1 more projectile."},
		{3, "Base Damage up by 20."},
		{4, "Passes through 2 more enemies."},
		{5, "Fires 1 more projectile."},
		{6, "Base Damage up by 20."},
		{7, "Passes through 2 more enemies."},
		{8, "Base Damage up by 20."},
	};
}

Axe::~Axe()
{
}

void Axe::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
}

void Axe::Tick(float _DeltaTime)
{
}

void Axe::InitCollision()
{
}

void Axe::Action()
{
}
