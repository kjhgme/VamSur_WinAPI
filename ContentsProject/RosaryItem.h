#pragma once
#include "DropItem.h"
class ARosaryItem : public ADropItem
{
public:
	ARosaryItem();
	~ARosaryItem();

	ARosaryItem(const ARosaryItem& _Other) = delete;
	ARosaryItem(ARosaryItem&& _Other) noexcept = delete;
	ARosaryItem& operator=(const ARosaryItem& _Other) = delete;
	ARosaryItem& operator=(ARosaryItem&& _Other) noexcept = delete;

protected:

private:

};

