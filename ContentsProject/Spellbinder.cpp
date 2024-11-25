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
}

void Spellbinder::Action()
{
}
