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
