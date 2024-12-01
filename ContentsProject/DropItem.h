#pragma once
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineSound.h>

class ADropItem : public AActor
{
public:
	ADropItem();
	~ADropItem();

	ADropItem(const ADropItem& _Other) = delete;
	ADropItem(ADropItem&& _Other) noexcept = delete;
	ADropItem& operator=(const ADropItem& _Other) = delete;
	ADropItem& operator=(ADropItem&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	// InitFunction
	void InitDropItem(FVector2D _Pos);
	virtual void InitCollision(FVector2D _Pos);

	// Function
	void CollisionEnter(AActor* _ColActor);
	virtual void ApplyItemEffect();
	void ItemToPlayer(float _DeltaTime);

	bool IsPickedUp = false;

protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
	FVector2D ItemPos{};
	FVector2D PlayerPos{};
	FVector2D KnockBack{};

	bool IsReturning = false;
	float KnockBackTime = 0.0f;

	USoundPlayer GetSoundPlayer;

private:

};

