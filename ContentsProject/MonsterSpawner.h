#pragma once
#include "Monster.h"

class AMonsterSpawner : public AActor
{
public:
	AMonsterSpawner();
	~AMonsterSpawner();

	AMonsterSpawner(const AMonsterSpawner& _Other) = delete;
	AMonsterSpawner(AMonsterSpawner&& _Other) noexcept = delete;
	AMonsterSpawner& operator=(const AMonsterSpawner& _Other) = delete;
	AMonsterSpawner& operator=(AMonsterSpawner&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime);

	void SpawnMonster();

	FVector2D CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle);

protected:

private:
	float Time = 0.0f;
	FVector2D Pos{};
	float CurAngle{};
	float MoveSpeed{};
	float SpawnSpeed{};
	std::list<AMonster*> Monsters;

	// testImage
	class USpriteRenderer* SpriteRenderer = nullptr;

};

