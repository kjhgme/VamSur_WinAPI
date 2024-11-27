#pragma once
#include "Weapon.h"
class EmptyTome : public AWeapon
{
public:
	EmptyTome();
	~EmptyTome();

	EmptyTome(const EmptyTome& _Other) = delete;
	EmptyTome(EmptyTome&& _Other) noexcept = delete;
	EmptyTome& operator=(const EmptyTome& _Other) = delete;
	EmptyTome& operator=(EmptyTome&& _Other) noexcept = delete;

	void BeginPlay() override;

	void Action() override;

	void LevelUp() override;

protected:

private:

};

