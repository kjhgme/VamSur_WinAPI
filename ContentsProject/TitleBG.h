#pragma once
#include <EngineCore/Actor.h>

class ATitleBG : public AActor
{
public:
	ATitleBG();
	~ATitleBG();

	ATitleBG(const ATitleBG& _Other) = delete;
	ATitleBG(ATitleBG&& _Other) noexcept = delete;
	ATitleBG& operator=(const ATitleBG& _Other) = delete;
	ATitleBG& operator=(ATitleBG&& _Other) noexcept = delete;

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
};

