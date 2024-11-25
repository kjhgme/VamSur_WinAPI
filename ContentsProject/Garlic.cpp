#include "PreCompile.h"
#include "Garlic.h"

Garlic::Garlic()
{
	WeaponType = EWeaponType::Garlic;

	LevelDescriptions = {
		{1, "Damages nearby enemies.\nReduces resistance to knockback."},
		{2, "Base Area up by 40%.\nBase Damage up by 2."},
		{3, "Cooldown reduced by 0.1 seconds.\nBase Damage up by 1."},
		{4, "Base Area up by 20%.\nBase Damage up by 1."},
		{5, "Cooldown reduced by 0.1 seconds.\nBase Damage up by 2."},
		{6, "Base Area up by 20%.\nBase Damage up by 1."},
		{7, "Cooldown reduced by 0.1 seconds.\nBase Damage up by 1."},
		{8, "Base Area up by 20%.\nBase Damage up by 1."},
	};
}

Garlic::~Garlic()
{
}

void Garlic::BeginPlay()
{
	AWeapon::BeginPlay();

	Level = 1;
	AttackPower = 10;
	KnockBack = 1;
}

void Garlic::Tick(float _DeltaTime)
{
}

void Garlic::InitCollision()
{
}

void Garlic::Action()
{
}

void Garlic::Attack()
{
}
