#pragma once
#include "DropItem.h"
class AOrologionItem : public ADropItem
{
public:
	AOrologionItem();
	~AOrologionItem();

	AOrologionItem(const AOrologionItem& _Other) = delete;
	AOrologionItem(AOrologionItem&& _Other) noexcept = delete;
	AOrologionItem& operator=(const AOrologionItem& _Other) = delete;
	AOrologionItem& operator=(AOrologionItem&& _Other) noexcept = delete;

protected:

private:

};

