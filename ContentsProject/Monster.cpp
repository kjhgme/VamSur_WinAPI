#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/EngineAPICore.h>

AMonster::AMonster()
{
	MonsterInit();
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	SetSprite();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChasePlayer(_DeltaTime);
}

void AMonster::MonsterInit()
{
	SetMonsterPos({ 100, 0 });

	SetMonsterStatus();
}

void AMonster::SetSprite()
{
}

void AMonster::SetMonsterStatus()
{
	//MonsterStatus.Health	= 0;
	//MonsterStatus.Power		= 0;
	//MonsterStatus.Speed		= 0;
	//MonsterStatus.KnockBack	= 0;
	//MonsterStatus.KBMax		= 0;
	//MonsterStatus.XP		= 0;
}

void AMonster::SetMonsterPos(FVector2D _pos)
{
	SetActorLocation(_pos);
}

void AMonster::ChasePlayer(float _DeltaTime)
{
	FVector2D MonsterPos = GetActorLocation();
	FVector2D PlayerPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	if (PlayerPos.X > MonsterPos.X)
		AddActorLocation({ MonsterStatus.Speed * _DeltaTime, 0.0f });
	else
		AddActorLocation({ -(MonsterStatus.Speed * _DeltaTime), 0.0f });


	if (PlayerPos.Y > MonsterPos.Y)
		AddActorLocation({ 0.0f, MonsterStatus.Speed * _DeltaTime });
	else
		AddActorLocation({ 0.0f, -(MonsterStatus.Speed * _DeltaTime) });

}
