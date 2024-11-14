#pragma once
#include "DropItem.h"

class AExpItem : public ADropItem
{
public:
	AExpItem();
	~AExpItem();

	AExpItem(const AExpItem& _Other) = delete;
	AExpItem(AExpItem&& _Other) noexcept = delete;
	AExpItem& operator=(const AExpItem& _Other) = delete;
	AExpItem& operator=(AExpItem&& _Other) noexcept = delete;

	void SetExp(float _Exp);

protected:

private:
	float Exp = 0.0f;
};

