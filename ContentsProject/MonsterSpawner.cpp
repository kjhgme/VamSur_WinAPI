#include "PreCompile.h"
#include "MonsterSpawner.h"

#include <cmath>

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

#include "MonsterStatus.h"

AMonsterSpawner::AMonsterSpawner()
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

	for (int i = 0; i < 3000; i++)
	{
		SpawnMonster(Ghoul1Status);
	}
}

void AMonsterSpawner::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	FVector2D playerPos = GetWorld()->GetMainPawn()->GetActorLocation();

	CurAngle += MoveSpeed * _DeltaTime;
	Pos =  CalculateCircularPosition(playerPos, 400.0f, CurAngle );
	
	SetActorLocation({ Pos });

	Time += _DeltaTime;
	if (SpawnSpeed <= Time)
	{
		SpawnMonster(Ghoul1Status);
		Time -= SpawnSpeed;
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

FVector2D AMonsterSpawner::CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle)
{
	float AngleInRadians = _CurAngle * (3.1415f / 180.0f);

	float X = Center.X + Radius * cos(AngleInRadians);
	float Y = Center.Y + Radius * sin(AngleInRadians);

	return FVector2D(X, Y);
}