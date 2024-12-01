#include "PreCompile.h"
#include "MonsterSpawner.h"

#include <cmath>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Level.h>
#include <EngineCore/EngineAPICore.h>

#include "InGameMode.h"
#include "MonsterStatus.h"
#include "ItemContainer.h"

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
	DebugOn();
}

void AMonsterSpawner::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	playerPos = GetWorld()->GetMainPawn()->GetActorLocation();

	CurAngle += MoveSpeed * _DeltaTime;
	Pos =  CalculateCircularPosition(playerPos, 400.0f, CurAngle );
	
	SetActorLocation({ Pos });


	if (true == UEngineInput::GetInst().IsDown(VK_F1))
	{
		SpawnMonster(CurStatus);
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F2))
	{
		SpawnBoss(CurBossStatus);
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F3))
	{
		SpawnMapEvent(CurMapEventStatus);
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F4))
	{
		AItemContainer* ItemContainer = GetWorld()->SpawnActor<AItemContainer>();
		ItemContainer->SetActorLocation(GetActorLocation());
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F5))
	{
		ChangeMonster();
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F6))
	{
		if (!BossQueue.empty())
		{
			CurBossStatus = BossQueue.front();
			BossQueue.pop();
		}
	}
	if (true == UEngineInput::GetInst().IsDown(VK_F7))
	{
		ChangeMapEventMonster();
	}
}

void AMonsterSpawner::InitSpawnerVersion(int _level)
{
	StageLevel = _level;
	if (0 == StageLevel)
	{
		// StatusQueue
		{
			StatusQueue.push(Bat3Status);

			StatusQueue.push(Ghoul1Status);
			SecondQueue.push(Bat1Status);

			StatusQueue.push(Bat1Status);
			SecondQueue.push(Bat2Status);
			ThirdQueue.push(Bat3Status);

			StatusQueue.push(Skeleton1Status);

			StatusQueue.push(Skeleton1Status);
			SecondQueue.push(Ghost1Status);

			StatusQueue.push(Mudman2Status);

			StatusQueue.push(Ghoul2Status);
			SecondQueue.push(Mudman2Status);

			StatusQueue.push(Bat2Status);
			SecondQueue.push(Bat3Status);
			ThirdQueue.push(Mudman1Status);

			StatusQueue.push(Ghoul2Status);

			StatusQueue.push(GiantBatStatus);
			SecondQueue.push(Ghoul1Status);

			StatusQueue.push(Mudman1Status);
			SecondQueue.push(Mudman2Status);

			StatusQueue.push(Skeleton1Status);

			StatusQueue.push(WerewolfStatus);
			SecondQueue.push(Ghost1Status);
			ThirdQueue.push(Skeleton1Status);

			StatusQueue.push(WerewolfStatus);
			SecondQueue.push(Ghost1Status);
			ThirdQueue.push(Ghost1Status);

			StatusQueue.push(GiantBatStatus);
			SecondQueue.push(WerewolfStatus);

			StatusQueue.push(WerewolfStatus);
			SecondQueue.push(GiantBatStatus);
			ThirdQueue.push(Mudman2Status);

			StatusQueue.push(MantichanaStatus);
			SecondQueue.push(Mudman1Status);
			ThirdQueue.push(Mudman2Status);

			StatusQueue.push(BigMummyStatus);

			StatusQueue.push(BigMummyStatus);
			SecondQueue.push(Mudman1Status);

			StatusQueue.push(BigMummyStatus);
			SecondQueue.push(Mudman1Status);

			StatusQueue.push(BigMummyStatus);
			SecondQueue.push(Mudman2Status);
			ThirdQueue.push(GiantBatStatus);

			StatusQueue.push(FlowerWallStatus);

			StatusQueue.push(FlowerWallStatus);
			SecondQueue.push(BigMummyStatus);

			StatusQueue.push(FlowerWallStatus);
			SecondQueue.push(BigMummyStatus);

			StatusQueue.push(FlowerWallStatus);
			SecondQueue.push(BigMummyStatus);

			StatusQueue.push(VenusStatus);

			StatusQueue.push(VenusStatus);
			SecondQueue.push(FlowerWallStatus);

			StatusQueue.push(BigMummyStatus);
			SecondQueue.push(Mudman1Status);
			ThirdQueue.push(Mudman2Status);

			StatusQueue.push(GiantBatStatus);
			SecondQueue.push(GlowingBatStatus);

			StatusQueue.push(GlowingBatStatus);
			SecondQueue.push(SilverBatStatus);

			StatusQueue.push(TheReaperStatus);
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
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(FlowerWallStatus);	
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(FlowerWallStatus);	
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Ghost1Status);		
			MapEventQueue.push(Ghost1Status);		
			MapEventQueue.push(FlowerWallStatus);	
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(FlowerWallStatus);	
			MapEventQueue.push(Ghost1Status);		
			MapEventQueue.push(Ghost1Status);		
			MapEventQueue.push(Bat1Status);			
			MapEventQueue.push(Bat1Status);			
		}
		// SpawnMonster
		{
			// FirstMonster
			{
				ChangeMonster();
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 0.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 1.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 1.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 2.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 2.0f);
				
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 3.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 3.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 4.0f);
				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 4.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 5.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 5.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 6.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 6.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 7.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 7.0f);

				TimeEventer.PushEvent(1.5f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 8.0f);
				TimeEventer.PushEvent(1.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 8.0f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 9.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 9.0f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 10.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 10.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 11.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 11.0f);

				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 12.0f);
				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 12.0f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 13.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 13.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 14.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 14.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 15.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 15.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 16.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 16.0f);

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 17.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 17.0f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 18.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 18.0f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 19.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 19.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 20.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 20.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 21.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 21.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 22.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 22.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 23.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 23.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 24.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 24.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 25.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 25.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 26.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 26.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 27.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 27.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 28.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 28.0f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMonster, this), false, -1.0f, false, 60.0f * 29.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnTimer, this), false, 60.0f, false, 60.0f * 29.0f);
			}
			// Second
			{
				ChangeSecondMonster();
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 1.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 2.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 2.0f + 1.0f);
				
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 4.0f + 1.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 4.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 6.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 6.0f + 1.0f);
				
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 7.0f + 1.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 7.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 9.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 9.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 10.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 10.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 12.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 12.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 13.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 13.0f + 1.0f);
				
				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 14.0f + 1.0f);
				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 14.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 15.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 15.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 16.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 16.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 18.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 18.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 19.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 19.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 20.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 20.0f + 1.0f);
				
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 22.0f + 1.0f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 22.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 23.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 23.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 24.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 24.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 26.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 26.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 27.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 27.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 28.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 28.0f + 1.0f);
				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeSecondMonster, this), false, -1.0f, false, 60.0f * 29.0f + 1.0f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnSecondTimer, this), false, 60.0f, false, 60.0f * 29.0f + 1.0f);
			}
			// Third
			{
				ChangeThirdMonster();

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 2.0f + 1.2f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 7.0f + 1.2f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 7.0f + 1.2f);

				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 12.0f + 1.2f);
				TimeEventer.PushEvent(0.25f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 12.0f + 1.2f);

				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 13.0f + 1.2f);
				TimeEventer.PushEvent(0.5f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 13.0f + 1.2f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 15.0f + 1.2f);
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 15.0f + 1.2f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 16.0f + 1.2f);				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 16.0f + 1.2f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 20.0f + 1.2f);				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 20.0f + 1.2f);

				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeThirdMonster, this), false, -1.0f, false, 60.0f * 27.0f + 1.2f);				
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::SpawnThirdTimer, this), false, 60.0f, false, 60.0f * 27.0f + 1.2f);
			}
			// BossMonster
			{
				TimeEventer.PushEvent(60.0f * 1.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 3.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 5.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 7.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 8.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 9.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 10.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 11.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 12.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 14.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 15.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 16.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 18.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 20.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 21.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 21.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 22.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 23.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 24.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 25.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 27.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 29.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
				TimeEventer.PushEvent(60.0f * 30.0f, std::bind(&AMonsterSpawner::SpawnBossTimer, this), false, -1.0f, false);
			}
			// MapEvents
			{
				ChangeMapEventMonster();

				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 3.0f, false, 60.0f * 2.0f);
																																	
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 3.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 2.0f, false, 60.0f * 3.0f);
																																
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 4.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 2.0f, false, 60.0f * 4.0f);
																																
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 5.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, -1.0f, false, 60.0f * 5.0f);
																															
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 6.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 2.0f, false, 60.0f * 6.0f);
																												
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 8.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 6.0f, false, 60.0f * 8.0f);
								
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 9.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 3.0f, false, 60.0f * 9.0f);
								
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 10.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, -1.0f, false, 60.0f * 10.0f);
																													
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 11.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 3.0f, false, 60.0f * 11.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 12.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, -1.0f, false, 60.0f * 12.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 13.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 21.0f, false, 60.0f * 13.0f);
								
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 13.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 21.0f, false, 60.0f * 13.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 15.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, -1.0f, false, 60.0f * 15.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 20.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 21.0f, false, 60.0f * 20.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 20.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 21.0f, false, 60.0f * 20.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 25.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 6.0f, false, 60.0f * 25.0f);
									  
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 27.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, -1.0f, false, 60.0f * 27.0f);
									 
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 27.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 20.0f, false, 60.0f * 27.0f);
									
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 29.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, -1.0f, false, 60.0f * 29.0f);
									 
				TimeEventer.PushEvent(0.1f, std::bind(&AMonsterSpawner::ChangeMapEventMonster, this), false, -1.0f, false, 60.0f * 29.0f);
				TimeEventer.PushEvent(1.0f, std::bind(&AMonsterSpawner::SpawnMapEventTimer, this), false, 1.0f * 20.0f, false, 60.0f * 29.0f);
			}
		}
	}
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

void AMonsterSpawner::SpawnSecondTimer()
{
	SpawnMonster(CurSecondStatus);
}

void AMonsterSpawner::SpawnThirdTimer()
{
	SpawnMonster(CurThirdStatus);
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
		CurBossStatus = BossQueue.front();
		BossQueue.pop();
	}

	SpawnBoss(CurBossStatus);
}

void AMonsterSpawner::SpawnMapEvent(MonsterStatus _Status)
{
	if (_Status.Name == "Bat1")
	{
		for (int i = 0; i < 7; ++i) {
			for (int j = 0; j < 7; ++j) {
				AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();
					
				if (nullptr != SpawnedMonster)
				{
					SpawnedMonster->InitMonster(_Status);
					SpawnedMonster->SetMonsterPos({ Pos.X + SpawnedMonster->GetMonsterSize().X * i + i , Pos.Y + SpawnedMonster->GetMonsterSize().Y * j + j });
					SpawnedMonster->SetMapEvent(true);
				}

				SpawnedMonsters.push_back(SpawnedMonster);
			}
		}
	}	
	else if (_Status.Name == "Flower1")
	{
		for (int i = 0; i < 100; ++i) {
			AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();

			if (nullptr != SpawnedMonster)
			{
				SpawnedMonster->InitMonster(_Status); 

				int PlayerLevel = AInGameMode::Player->GetLevel();
				SpawnedMonster->SetHp(_Status.Hp * PlayerLevel);

				FVector2D newMonsterPos = CalculateCircularPosition(playerPos, 800.0f, (360.0f / 100) * i);
				SpawnedMonster->SetMonsterPos(newMonsterPos);
			}

			SpawnedMonsters.push_back(SpawnedMonster);
		}
	}
	else if (_Status.Name == "Ghost")
	{
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				AMonster* SpawnedMonster = GetWorld()->SpawnActor<AMonster>();

				if (nullptr != SpawnedMonster)
				{
					SpawnedMonster->InitMonster(_Status);
					SpawnedMonster->SetMonsterPos({ Pos.X + SpawnedMonster->GetMonsterSize().X * i + i , Pos.Y + SpawnedMonster->GetMonsterSize().Y * j + j });
					SpawnedMonster->SetMapEvent(true);
				}

				SpawnedMonsters.push_back(SpawnedMonster);
			}
		}
	}
	
}

void AMonsterSpawner::SpawnMapEventTimer()
{
	SpawnMapEvent(CurMapEventStatus);
}

void AMonsterSpawner::ChangeMonster()
{
	if (!StatusQueue.empty())
	{
		CurStatus = StatusQueue.front();
		StatusQueue.pop();
	}
}

void AMonsterSpawner::ChangeSecondMonster()
{
	if (!SecondQueue.empty())
	{
		CurSecondStatus = SecondQueue.front();
		SecondQueue.pop();
	}
}

void AMonsterSpawner::ChangeThirdMonster()
{
	if (!ThirdQueue.empty())
	{
		CurThirdStatus = ThirdQueue.front();
		ThirdQueue.pop();
	}
}

void AMonsterSpawner::ChangeMapEventMonster()
{
	if (!MapEventQueue.empty())
	{
		CurMapEventStatus = MapEventQueue.front();
		MapEventQueue.pop();
	}
}

FVector2D AMonsterSpawner::CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle)
{
	float AngleInRadians = _CurAngle * (3.1415f / 180.0f);

	float X = Center.X + Radius * cos(AngleInRadians);
	float Y = Center.Y + Radius * sin(AngleInRadians);

	return FVector2D(X, Y);
}
