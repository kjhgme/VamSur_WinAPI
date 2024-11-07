#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/EngineAPICore.h>
 
AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	InitCreateMonAnim();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChasePlayer(_DeltaTime);

	ChangeAnimation();
}

void AMonster::MonsterInit()
{
	InitSprite();
	InitMonsterStatus();
}

void AMonster::InitCreateMonAnim()
{
	std::string name = MonsterStatus.Name;
	SpriteRenderer->CreateAnimation(std::string_view(name + "_L_Idle"), std::string_view(name + "_L"), 16, 19, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_L_Die"), std::string_view(name + "_L"), 0, 15, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_R_Idle"), std::string_view(name + "_R"), 16, 19, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_R_Die"), std::string_view(name + "_R"), 0, 15, 0.15f);
	// SpriteRenderer->ChangeAnimation(std::string_view(name + "_L_Idle"));
}

void AMonster::SetMonsterPos(FVector2D _pos)
{
	SetActorLocation(_pos);
}

void AMonster::ChasePlayer(float _DeltaTime)
{
	FVector2D MonsterPos = GetActorLocation();
	FVector2D PlayerPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	if (true == Alive)
	{
		if (PlayerPos.X > MonsterPos.X)
		{
			HeadDirRight = true;
			AddActorLocation({ MonsterStatus.Speed * _DeltaTime, 0.0f });
		}
		else
		{
			HeadDirRight = false;
			AddActorLocation({ -(MonsterStatus.Speed * _DeltaTime), 0.0f });
		}

		if (PlayerPos.Y > MonsterPos.Y)
			AddActorLocation({ 0.0f, MonsterStatus.Speed * _DeltaTime });
		else
			AddActorLocation({ 0.0f, -(MonsterStatus.Speed * _DeltaTime) });
	}

}

void AMonster::ChangeAnimation()
{
	if (true == Alive)
	{
		if (false == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(MonsterStatus.Name + "_L_Idle"));
		}
		else if (true == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(MonsterStatus.Name + "_R_Idle"));
		}
	}
	else
	{
		if (false == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(MonsterStatus.Name + "_L_Die"));
		}
		else if (true == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(MonsterStatus.Name + "_R_Die"));
		}
	}
}
