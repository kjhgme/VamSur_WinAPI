#pragma once
#include "Weapon.h"
class MagicWand : public AWeapon
{
public:
	MagicWand();
	~MagicWand();

	MagicWand(const MagicWand& _Other) = delete;
	MagicWand(MagicWand&& _Other) noexcept = delete;
	MagicWand& operator=(const MagicWand& _Other) = delete;
	MagicWand& operator=(MagicWand&& _Other) noexcept = delete;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision() override;

	void Action() override;

protected:

private:

};

