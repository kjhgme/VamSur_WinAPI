#include "PreCompile.h"
#include "EmptyTome.h"

EmptyTome::EmptyTome()
{
	WeaponType = EWeaponType::EmptyTome;

	LevelDescriptions = {
		{1, "Reduces weapons cooldown by 8%"},
		{2, "Cooldown reduced by 8.0%"},
		{3, "Cooldown reduced by 8.0%"},
		{4, "Cooldown reduced by 8.0%"},
		{5, "Cooldown reduced by 8.0%"},
	};
}

EmptyTome::~EmptyTome()
{
}

void EmptyTome::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
	Cooldown += 8.0f;
}

void EmptyTome::Action()
{
}

void EmptyTome::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Cooldown += 8.0f;
		break;
	case 3:
		Cooldown += 8.0f;
		break;
	case 4:
		Cooldown += 8.0f;
		break;
	case 5:
		Cooldown += 8.0f;
		break;
	}
}