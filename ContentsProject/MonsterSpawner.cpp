#include "PreCompile.h"
#include "MonsterSpawner.h"

#include <cmath>

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

#include "MonsterStatus.h"

AMonsterSpawner::AMonsterSpawner()
{
}

AMonsterSpawner::AMonsterSpawner(int _level)
{
}

AMonsterSpawner::~AMonsterSpawner()
{
}

void AMonsterSpawner::BeginPlay()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Stage", 1);
	SpriteRenderer->SetComponentScale({ 38, 42 });
}

void AMonsterSpawner::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D playerPos = GetWorld()->GetMainPawn()->GetActorLocation();

	CurAngle += MoveSpeed * _DeltaTime;
	Pos =  CalculateCircularPosition(playerPos, 400.0f, CurAngle );
	
	SetActorLocation({ Pos });

	Time += _DeltaTime;
	SpawnTime += _DeltaTime;
	if (SpawnSpeed <= SpawnTime)
	{
		if (Time >= 3.0f)
		{
			SpawnMonster(Ghoul1Status);
		}
		else {
			SpawnMonster(Bat1Status);
		}
		SpawnTime -= SpawnSpeed;
	}
}

void AMonsterSpawner::SpawnMonster(MonsterStatus _Status)
{
	AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();
	if (nullptr != SpawnedMonster)
	{
		SpawnedMonster->InitMonster(_Status);
		SpawnedMonster->SetMonsterPos(Pos);
		SpawnedMonsters.push_back(SpawnedMonster);
	}
}

void AMonsterSpawner::SpawnerVersion(float _DeltaTime)
{
}

FVector2D AMonsterSpawner::CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle)
{
	float AngleInRadians = _CurAngle * (3.1415f / 180.0f);

	float X = Center.X + Radius * cos(AngleInRadians);
	float Y = Center.Y + Radius * sin(AngleInRadians);

	return FVector2D(X, Y);
}