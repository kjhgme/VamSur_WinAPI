#include "PreCompile.h"
#include "Spellbinder.h"

Spellbinder::Spellbinder()
{
	WeaponType = EWeaponType::Spellbinder;

	LevelDescriptions = {
		{1, "Increases duration of weapon\neffects by 10%"},
		{2, "Effect lasts 10% longer."},
		{3, "Effect lasts 10% longer."},
		{4, "Effect lasts 10% longer."},
		{5, "Effect lasts 10% longer."},
	};
}

Spellbinder::~Spellbinder()
{
}

void Spellbinder::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
	Duration += 10.0f;
}

void Spellbinder::Action()
{
}

void Spellbinder::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Duration += 10.0f;
		break;
	case 3:
		Duration += 10.0f;
		break;
	case 4:
		Duration += 10.0f;
		break;
	case 5:
		Duration += 10.0f;
		break;
	}
}