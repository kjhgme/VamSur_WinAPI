#pragma once
#include <EngineCore/Actor.h>

class ATitleImelda : public AActor
{
public:
	ATitleImelda();
	~ATitleImelda();

	ATitleImelda(const ATitleImelda& _Other) = delete;
	ATitleImelda(ATitleImelda&& _Other) noexcept = delete;
	ATitleImelda& operator=(const ATitleImelda& _Other) = delete;
	ATitleImelda& operator=(ATitleImelda&& _Other) noexcept = delete;

	void FadeIn();

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;

	float FadeValue = 0.0f;
};

