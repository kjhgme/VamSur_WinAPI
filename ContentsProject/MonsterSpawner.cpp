#include "PreCompile.h"
#include "MonsterSpawner.h"

#include <cmath>

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

#include "MonsterStatus.h"

AMonsterSpawner::AMonsterSpawner()
{
	InitSpawnerVersion(0);
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
}

void AMonsterSpawner::InitSpawnerVersion(int _level)
{
	StageLevel = _level;
	if (0 == StageLevel)
	{
		StatusQueue.push(Bat1Status);
		StatusQueue.push(Ghoul1Status);
	}

	ChangeMonster();



	TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), 6.0f);
	TimeEventer.PushEvent(4.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), 3.0f, false);
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

void AMonsterSpawner::SpawnTimer()
{
	SpawnMonster(CurStatus);
}

void AMonsterSpawner::ChangeMonster()
{
	if (!StatusQueue.empty())
	{
		CurStatus = StatusQueue.front();
		StatusQueue.pop();
	}
}

FVector2D AMonsterSpawner::CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle)
{
	float AngleInRadians = _CurAngle * (3.1415f / 180.0f);

	float X = Center.X + Radius * cos(AngleInRadians);
	float Y = Center.Y + Radius * sin(AngleInRadians);

	return FVector2D(X, Y);
}