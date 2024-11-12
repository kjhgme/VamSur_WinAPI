#pragma once

#include <string.h>
#include <EngineCore/2DCollision.h>
#include "MonsterStatus.h"

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitMonster(MonsterStatus _Type);
	void InitMonsterStatus(MonsterStatus _Type);
	void InitSprite();
	void InitCreateMonAnim();
	void InitCollision();

	// SetFunction
	void SetMonsterPos(FVector2D _pos);

	// Function
	void ChasePlayer(float _DeltaTime);
	void ChangeAnimation();
	void Die(float _DeltaTime);

protected:
	MonsterStatus Status;
	
	class USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;

private:
	bool HeadDirRight = false;
	bool Alive = true;

	FVector2D MonsterPos{};
	FVector2D PlayerPos{};
	FVector2D DiffPos{};
	// static std::map<MonsterTypem, >
};

