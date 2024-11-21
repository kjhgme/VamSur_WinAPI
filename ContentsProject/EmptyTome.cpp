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
}

void EmptyTome::Action()
{
}
