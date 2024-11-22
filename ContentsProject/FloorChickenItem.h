#pragma once
#include "DropItem.h"
class AFloorChickenItem : public ADropItem
{
public:
	AFloorChickenItem();
	~AFloorChickenItem();


	AFloorChickenItem(const AFloorChickenItem& _Other) = delete;
	AFloorChickenItem(AFloorChickenItem&& _Other) noexcept = delete;
	AFloorChickenItem& operator=(const AFloorChickenItem& _Other) = delete;
	AFloorChickenItem& operator=(AFloorChickenItem&& _Other) noexcept = delete;

	void SetHp(float _Hp);
	void ApplyItemEffect() override;

protected:

private:
	float Hp = 30.0f;
};

