#pragma once
#include <EngineCore/2DCollision.h>

class ADropItem : public AActor
{
public:
	ADropItem();
	~ADropItem();

	ADropItem(const ADropItem& _Other) = delete;
	ADropItem(ADropItem&& _Other) noexcept = delete;
	ADropItem& operator=(const ADropItem& _Other) = delete;
	ADropItem& operator=(ADropItem&& _Other) noexcept = delete;

	// InitFunction
	void InitDropItem(FVector2D _Pos);
	void InitCollision(FVector2D _Pos);

	// Function
	void CollisionEnter(AActor* _ColActor);

protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
	FVector2D Pos{};

private:

};

