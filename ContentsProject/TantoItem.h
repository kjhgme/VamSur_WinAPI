#pragma once
#include "DropItem.h"
class ATantoItem : public ADropItem
{
public:
	ATantoItem();
	~ATantoItem();

	ATantoItem(const ATantoItem& _Other) = delete;
	ATantoItem(ATantoItem&& _Other) noexcept = delete;
	ATantoItem& operator=(const ATantoItem& _Other) = delete;
	ATantoItem& operator=(ATantoItem&& _Other) noexcept = delete;

	void ApplyItemEffect() override;

protected:

private:
};

