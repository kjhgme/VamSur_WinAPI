#pragma once
#include "DropItem.h"
class AVacuumItem : public ADropItem
{
public:
	AVacuumItem();
	~AVacuumItem();

	AVacuumItem(const AVacuumItem& _Other) = delete;
	AVacuumItem(AVacuumItem&& _Other) noexcept = delete;
	AVacuumItem& operator=(const AVacuumItem& _Other) = delete;
	AVacuumItem& operator=(AVacuumItem&& _Other) noexcept = delete;

	void ApplyItemEffect() override;

protected:

private:

};

