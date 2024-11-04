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

protected:

private:
	float Time = 0.0f;
	FVector2D Pos{};
	std::list<AMonster*> Monsters;
};

