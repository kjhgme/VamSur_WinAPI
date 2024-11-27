#pragma once
#include "DropItem.h"

class AChestItem : public ADropItem
{
public:
	AChestItem();
	~AChestItem();

	AChestItem(const AChestItem& _Other) = delete;
	AChestItem(AChestItem&& _Other) noexcept = delete;
	AChestItem& operator=(const AChestItem& _Other) = delete;
	AChestItem& operator=(AChestItem&& _Other) noexcept = delete;

	void InitCollision(FVector2D _Pos) override;

	void TakeChest();
	void ApplyItemEffect() override;

protected:

private:
	class USpriteRenderer* CursorRenderer = nullptr;
};

