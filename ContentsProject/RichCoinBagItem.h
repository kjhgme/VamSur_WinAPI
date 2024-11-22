#pragma once
#include "DropItem.h"
class ARichCoinBagItem : public ADropItem
{
public:
	ARichCoinBagItem();
	~ARichCoinBagItem();

	ARichCoinBagItem(const ARichCoinBagItem& _Other) = delete;
	ARichCoinBagItem(ARichCoinBagItem&& _Other) noexcept = delete;
	ARichCoinBagItem& operator=(const ARichCoinBagItem& _Other) = delete;
	ARichCoinBagItem& operator=(ARichCoinBagItem&& _Other) noexcept = delete;

	void SetGold(int _Gold);
	void ApplyItemEffect() override;

protected:

private:
	int Gold = 100;
};

