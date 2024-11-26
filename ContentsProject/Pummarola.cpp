#include "PreCompile.h"
#include "Pummarola.h"

Pummarola::Pummarola()
{
	WeaponType = EWeaponType::Pummarola;

	LevelDescriptions = {
		{1, "Character recovers 0.2 HP\nper second."},
		{2, "Health recovery increases\nby 0.2 HP per second."},
		{3, "Health recovery increases\nby 0.2 HP per second."},
		{4, "Health recovery increases\nby 0.2 HP per second."},
		{5, "Health recovery increases\nby 0.2 HP per second."},
	};
}

Pummarola::~Pummarola()
{
}

void Pummarola::BeginPlay()
{
	Level = 1;
	Recovery += 0.2f;
}

void Pummarola::Action()
{
}

void Pummarola::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Recovery += 0.2f;
		break;
	case 3:
		Recovery += 0.2f;
		break;
	case 4:
		Recovery += 0.2f;
		break;
	case 5:
		Recovery += 0.2f;
		break;
	}
}