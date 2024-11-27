#include "PreCompile.h"
#include "MonsterSpawner.h"

#include <cmath>

#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

#include "InGameMode.h"
#include "MonsterStatus.h"

AMonsterSpawner::AMonsterSpawner()
{
	SetActorLocation({ 400.0f, 0.0f });
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
		// StatusQueue
		{
			StatusQueue.push(Bat3Status);

			//StatusQueue.push(Ghoul1Status);
			//StatusQueue.push(Bat1Status);
			//StatusQueue.push(Ghoul1Status);
			//StatusQueue.push(Bat1Status);

			//StatusQueue.push(Bat1Status);
			//StatusQueue.push(Bat2Status);
			//StatusQueue.push(Bat3Status);

			//StatusQueue.push(Skeleton1Status);
			//
			//StatusQueue.push(Skeleton1Status);
			//StatusQueue.push(Ghost1Status);

			//StatusQueue.push(Mudman2Status);

			//StatusQueue.push(Ghoul1Status);
			//StatusQueue.push(Mudman2Status);

			//StatusQueue.push(Bat2Status);
			//StatusQueue.push(Bat3Status);
			//StatusQueue.push(Mudman1Status);

			//StatusQueue.push(Ghoul1Status);

			//StatusQueue.push(GiantBatStatus);
			//StatusQueue.push(Ghoul1Status);

			//StatusQueue.push(Mudman1Status);
			//StatusQueue.push(Mudman2Status);

			//StatusQueue.push(Skeleton1Status);

			//StatusQueue.push(WerewolfStatus);
			//StatusQueue.push(Ghost1Status);
			//StatusQueue.push(Skeleton1Status);

			//StatusQueue.push(WerewolfStatus);
			//StatusQueue.push(Ghost1Status);		// *2

			//StatusQueue.push(GiantBatStatus);
			//StatusQueue.push(WerewolfStatus);

			//StatusQueue.push(WerewolfStatus);
			//StatusQueue.push(GiantBatStatus);
			//StatusQueue.push(Mudman2Status);

			//StatusQueue.push(MantichanaStatus);
			//StatusQueue.push(Mudman1Status);
			//StatusQueue.push(Mudman2Status);

			//StatusQueue.push(BigMummyStatus);

			//StatusQueue.push(BigMummyStatus);
			//StatusQueue.push(Mudman1Status);

			//StatusQueue.push(BigMummyStatus);
			//StatusQueue.push(Mudman1Status);

			//StatusQueue.push(BigMummyStatus);
			//StatusQueue.push(Mudman2Status);
			//StatusQueue.push(GiantBatStatus);

			//StatusQueue.push(FlowerWallStatus);

			//StatusQueue.push(FlowerWallStatus);
			//StatusQueue.push(BigMummyStatus);

			//StatusQueue.push(FlowerWallStatus);
			//StatusQueue.push(BigMummyStatus);

			//StatusQueue.push(FlowerWallStatus);
			//StatusQueue.push(BigMummyStatus);

			//StatusQueue.push(VenusStatus);

			//StatusQueue.push(VenusStatus);
			//StatusQueue.push(FlowerWallStatus);

			//StatusQueue.push(BigMummyStatus);
			//StatusQueue.push(Mudman1Status);
			//StatusQueue.push(Mudman2Status);

			//StatusQueue.push(GiantBatStatus);
			//StatusQueue.push(GlowingBatStatus);

			//StatusQueue.push(GlowingBatStatus);
			//StatusQueue.push(SilverBatStatus);

			//StatusQueue.push(TheReaperStatus);
		}
		// BossQueue
		{
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(MantichanaStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(GiantBatStatus);
			BossQueue.push(SilverBatStatus);
			BossQueue.push(MantichanaStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(SilverBatStatus);
			BossQueue.push(WerewolfLordStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(SilverBatStatus);
			BossQueue.push(MummyLordStatus);
			BossQueue.push(VenusStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(SilverBatStatus);
			BossQueue.push(VenusStatus);
			BossQueue.push(VenusLordStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(GlowingBatStatus);
			BossQueue.push(TheReaperStatus);
		}
		// MapEventQueue
		{
			// BatSwam * 3
			// BatSwam * 2
			// BatSwam * 2
			// FlowerWall
			// BatSwam * 2
			// BatSwam * 6
			// BatSwam * 3
			// BatSwam * 3
			// FlowerWall
			// BatSwam * 2
			// BatSwam * 2
			// GhostSwam * 21
			// GhostSwam * 21
			// FlowerWall
			// BatSwam * 21
			// BatSwam * 21
			// FlowerWall * 6
			// GhostSwam
			// GhostSwam * 20
			// BatSwam
			// BatSwam * 20
			//

		}
	}

	//ChangeMonster();

	//TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, -1.0f, true);// , 60.0f * 30.0f);
	
	//TimeEventer.PushEvent(3.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, 9.0f, false);

	TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
}

void AMonsterSpawner::SpawnMonster(MonsterStatus _Status)
{
	AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();
	if (nullptr != SpawnedMonster)
	{
		SpawnedMonster->InitMonster(_Status);
		SpawnedMonster->SetMonsterPos(Pos);

		if (true == _Status.HaveSkill)
		{
			int PlayerLevel = AInGameMode::Player->GetLevel();
			SpawnedMonster->SetHp(_Status.Hp * PlayerLevel);
		}

		SpawnedMonsters.push_back(SpawnedMonster);
	}
}

void AMonsterSpawner::SpawnTimer()
{
	SpawnMonster(CurStatus);
}

void AMonsterSpawner::SpawnBoss(MonsterStatus _Status)
{
	AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();
	if (nullptr != SpawnedMonster)
	{
		SpawnedMonster->InitMonster(_Status);
		SpawnedMonster->SetMonsterPos(Pos);

		if (true == _Status.HaveSkill)
		{
			int PlayerLevel = AInGameMode::Player->GetLevel();
			SpawnedMonster->SetHp(_Status.Hp * PlayerLevel);
		}

		SpawnedMonster->SetChest(true);

		SpawnedMonsters.push_back(SpawnedMonster);
	}
}

void AMonsterSpawner::SpawnBossTimer()
{
	if (!BossQueue.empty())
	{
		SpawnBoss(BossQueue.front());
		BossQueue.pop();
	}
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
