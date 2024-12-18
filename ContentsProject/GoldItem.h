﻿#pragma once
#include "DropItem.h"
class AGoldItem : public ADropItem
{
public:
	AGoldItem();
	~AGoldItem();

	AGoldItem(const AGoldItem& _Other) = delete;
	AGoldItem(AGoldItem&& _Other) noexcept = delete;
	AGoldItem& operator=(const AGoldItem& _Other) = delete;
	AGoldItem& operator=(AGoldItem&& _Other) noexcept = delete;

	void SetGold(int _Gold);
	void ApplyItemEffect() override;

protected:

private:
	int Gold = 1;
};

