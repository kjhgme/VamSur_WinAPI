#include "PreCompile.h"
#include "Spinach.h"

Spinach::Spinach()
{
	WeaponType = EWeaponType::Spinach;

	LevelDescriptions = {
		{1, "Raises inflicted damage by 10%"},
		{2, "Base damage up by 10%"},
		{3, "Base damage up by 10%"},
		{4, "Base damage up by 10%"},
		{5, "Base damage up by 10%"},
	};
}

Spinach::~Spinach()
{
}

void Spinach::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
}

void Spinach::Action()
{
}
