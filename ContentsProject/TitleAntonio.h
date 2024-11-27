﻿#pragma once
#include <EngineCore/Actor.h>

class ATitleAntonio : public AActor
{
public:
	ATitleAntonio();
	~ATitleAntonio();

	ATitleAntonio(const ATitleAntonio& _Other) = delete;
	ATitleAntonio(ATitleAntonio&& _Other) noexcept = delete;
	ATitleAntonio& operator=(const ATitleAntonio& _Other) = delete;
	ATitleAntonio& operator=(ATitleAntonio&& _Other) noexcept = delete;

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
};

