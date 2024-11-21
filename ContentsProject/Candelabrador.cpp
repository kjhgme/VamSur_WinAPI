#include "PreCompile.h"
#include "Candelabrador.h"

Candelabrador::Candelabrador()
{
	WeaponType = EWeaponType::Candelabrador;

	LevelDescriptions = {
		{1, "Augments area of attacks by 10%"},
		{2, "Base area up by 10%"},
		{3, "Base area up by 10%"},
		{4, "Base area up by 10%"},
		{5, "Base area up by 10%"},
	};
}

Candelabrador::~Candelabrador()
{
}

void Candelabrador::BeginPlay()
{
	Super::BeginPlay();

	Level = 1;
}

void Candelabrador::Action()
{
}
