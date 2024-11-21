#pragma once
#include "Weapon.h"
class HollowHeart : public AWeapon
{
public:
	HollowHeart();
	~HollowHeart();

	HollowHeart(const HollowHeart& _Other) = delete;
	HollowHeart(HollowHeart&& _Other) noexcept = delete;
	HollowHeart& operator=(const HollowHeart& _Other) = delete;
	HollowHeart& operator=(HollowHeart&& _Other) noexcept = delete;

protected:

private:

};

