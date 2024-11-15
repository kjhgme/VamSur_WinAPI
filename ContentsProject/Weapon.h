#pragma once
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineSound.h>

class AWeapon : public AActor
{
public:
	AWeapon();
	~AWeapon();

	AWeapon(const AWeapon& _Other) = delete;
	AWeapon(AWeapon&& _Other) noexcept = delete;
	AWeapon& operator=(const AWeapon& _Other) = delete;
	AWeapon& operator=(AWeapon&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void InitCollision() {};

	virtual void Action();
	virtual void ChangeHeadDir();

	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

protected:
	USpriteRenderer* IconSpriteRenderer = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	std::vector<U2DCollision*> CollisionComponents;
	
	int Level = 0;
	int AttackPower = 0;
	float KnockBack = 0;

	bool HeadDirRight = true;

private:
	FVector2D PlayerPos{0, 0};

	USoundPlayer HitSoundPlayer;
};

