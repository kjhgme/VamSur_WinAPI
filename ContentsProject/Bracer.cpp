#include "PreCompile.h"
#include "Bracer.h"

Bracer::Bracer()
{
	WeaponType = EWeaponType::Bracer;

	LevelDescriptions = {
		{1, "Increases projectiles speed by 10%"},
		{2, "Base speed up by 10%"},
		{3, "Base speed up by 10%"},
		{4, "Base speed up by 10%"},
		{5, "Base speed up by 10%"},
	};
}

Bracer::~Bracer()
{
}

void Bracer::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
	Speed += 20.0f;
}

void Bracer::Action()
{
}

void Bracer::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Speed += 20.0f;
		break;
	case 3:
		Speed += 20.0f;
		break;
	case 4:
		Speed += 20.0f;
		break;
	case 5:
		Speed += 20.0f;
		break;
	}
}