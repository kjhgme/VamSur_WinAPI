#include "PreCompile.h"
#include "HollowHeart.h"

HollowHeart::HollowHeart()
{
	WeaponType = EWeaponType::HollowHeart;

	LevelDescriptions = {
		{1, "Augment max health by 20%"},
		{2, "Max health increases by 20%"},
		{3, "Max health increases by 20%"},
		{4, "Max health increases by 20%"},
		{5, "Max health increases by 20%"},
	};
}

HollowHeart::~HollowHeart()
{
}
