#pragma once
#include "Monster.h"

#include <queue>

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
	
	void InitSpawnerVersion(int _level);

	std::list<AMonster*> GetMonsters()
	{
		std::list<AMonster*> LimitedMonsters;

		if (SpawnedMonsters.size() > 100)
		{
			auto it = SpawnedMonsters.begin();
			std::advance(it, 100);
			LimitedMonsters.insert(LimitedMonsters.begin(), SpawnedMonsters.begin(), it);
		}
		else
		{
			LimitedMonsters = SpawnedMonsters;
		}

		return LimitedMonsters;
	}

	void SpawnMonster(MonsterStatus _Status);
	void SpawnTimer();

	void SpawnBoss(MonsterStatus _Status);
	void SpawnBossTimer();

	void ChangeMonster();

	FVector2D CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle);

	std::list<AMonster*> SpawnedMonsters;

protected:

private:
	int StageLevel = 0;
	float Time = 0.0f;
	float SpawnTime = 0.0f;
	FVector2D Pos{};
	float CurAngle{};
	float MoveSpeed = 50.0f;
	float SpawnSpeed = 1.0f;
	std::queue<MonsterStatus> StatusQueue;
	std::queue<MonsterStatus> BossQueue;
	std::queue<MonsterStatus> MapEventQueue;
	MonsterStatus CurStatus = Bat1Status;

	// testImage
	class USpriteRenderer* SpriteRenderer = nullptr;

};

