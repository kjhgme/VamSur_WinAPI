#include "PreCompile.h"
#include "Monster.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineInput.h>
 
AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ChasePlayer(_DeltaTime);

	ChangeAnimation();

	if (true == UEngineInput::GetInst().IsDown('F'))
	{
		Alive = false;
		Destroy(2.0f);
	}
}

void AMonster::MonsterInit()
{
	InitSprite();
	InitMonsterStatus();
	InitCreateMonAnim();
	InitCollision();

	DebugOn();
}

void AMonster::InitCreateMonAnim()
{
	std::string name = MonsterStatus.Name;
	SpriteRenderer->CreateAnimation(std::string_view(name + "_L_Idle"), std::string_view(name + "_L"), 16, 19, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_L_Die"), std::string_view(name + "_L"), 0, 14, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_R_Idle"), std::string_view(name + "_R"), 16, 19, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_R_Die"), std::string_view(name + "_R"), 0, 14, 0.15f);
}

void AMonster::InitCollision()
{
	FVector2D scale =SpriteRenderer->GetComponentScale();

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0, 0 });
	CollisionComponent->SetComponentScale(scale);
	CollisionComponent->SetCollisionGroup(ECollisionGroup::MonsterBody);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);
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
