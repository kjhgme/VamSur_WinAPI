#pragma once
#include <EngineCore/Actor.h>

class ATitleVillain : public AActor
{
public:
	ATitleVillain();
	~ATitleVillain();

	ATitleVillain(const ATitleVillain& _Other) = delete;
	ATitleVillain(ATitleVillain&& _Other) noexcept = delete;
	ATitleVillain& operator=(const ATitleVillain& _Other) = delete;
	ATitleVillain& operator=(ATitleVillain&& _Other) noexcept = delete;

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
};

