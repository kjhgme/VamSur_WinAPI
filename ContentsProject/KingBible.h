#pragma once
#include "Weapon.h"
class KingBible : public AWeapon
{
public:
	KingBible();
	~KingBible();

	KingBible(const KingBible& _Other) = delete;
	KingBible(KingBible&& _Other) noexcept = delete;
	KingBible& operator=(const KingBible& _Other) = delete;
	KingBible& operator=(KingBible&& _Other) noexcept = delete;

protected:

private:

};

