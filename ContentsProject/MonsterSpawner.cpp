#include "PreCompile.h"
#include "MonsterSpawner.h"

#include <EngineCore/Level.h>


AMonsterSpawner::AMonsterSpawner()
{
}

AMonsterSpawner::~AMonsterSpawner()
{
}

void AMonsterSpawner::BeginPlay()
{
	Pos = GetWorld()->GetMainPawn()->GetActorLocation();
	Pos.X += 100;

	AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();
	if (nullptr != SpawnedMonster)
	{
		SpawnedMonster->MonsterInit(Pos);
	}

	Monsters.push_back(SpawnedMonster);
}

void AMonsterSpawner::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Time += _DeltaTime;

	if (1.0f <= Time)
	{
		SpawnMonster();
		Time = 0.0;
	}
}

void AMonsterSpawner::SpawnMonster()
{
	Pos = GetWorld()->GetMainPawn()->GetActorLocation();
	Pos.X += 100;

	AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();
	if (nullptr != SpawnedMonster)
	{
		SpawnedMonster->MonsterInit(Pos);
	}

	Monsters.push_back(SpawnedMonster);
}
