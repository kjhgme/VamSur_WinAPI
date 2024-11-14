#include "PreCompile.h"
#include "Monster.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>
#include "Player.h"

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

	if ("None" != Status.Name)
	{
		ChasePlayer(_DeltaTime);

		ChangeAnimation();

		if (true == UEngineInput::GetInst().IsDown('F'))
		{
			Die();
		}
	}
}

void AMonster::InitMonster(MonsterStatus _Type)
{
	InitMonsterStatus(_Type);
	InitSprite();
	InitCreateMonAnim();
	InitCollision();
	
	DebugOn();
}

void AMonster::InitMonsterStatus(MonsterStatus _Type)
{
	Status = _Type;

	if (true == Status.HaveSkill)
	{
		int PlayerLevel = APlayer::GetLevel();
		Status.Hp = Status.Hp * PlayerLevel;
	}
}

void AMonster::InitSprite()
{
	std::string name = Status.Name;

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::MONSTER);
	SpriteRenderer->SetSprite(name + "_L", 0);

	SpriteRenderer->SetSpriteScale(1.0f);
}

void AMonster::InitCreateMonAnim()
{
	std::string name = Status.Name;
	SpriteRenderer->CreateAnimation(std::string_view(name + "_L_Idle"), std::string_view(name + "_L"), 16, 19, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_L_Die"), std::string_view(name + "_L"), 0, 14, 0.05f, false);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_R_Idle"), std::string_view(name + "_R"), 16, 19, 0.15f);
	SpriteRenderer->CreateAnimation(std::string_view(name + "_R_Die"), std::string_view(name + "_R"), 0, 14, 0.05f, false);
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
	if (true == Alive)
	{
		MonsterPos = GetActorLocation();
		PlayerPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

		if (PlayerPos.X > MonsterPos.X)
		{
			HeadDirRight = true;
			AddActorLocation({ Status.Speed * _DeltaTime, 0.0f });
		}
		else
		{
			HeadDirRight = false;
			AddActorLocation({ -(Status.Speed * _DeltaTime), 0.0f });
		}

		if (PlayerPos.Y > MonsterPos.Y)
			AddActorLocation({ 0.0f, Status.Speed * _DeltaTime });
		else
			AddActorLocation({ 0.0f, -(Status.Speed * _DeltaTime) });
	}
	else 
	{
		float KnockBackX = UEngineMath::Clamp(DiffPos.X, -2.0f, 2.0f);
		float KnockBackY = UEngineMath::Clamp(DiffPos.Y, -2.0f, 2.0f);

		if (PlayerPos.X > MonsterPos.X)
		{
			HeadDirRight = true;
			AddActorLocation({ -(KnockBackX * Status.Speed * _DeltaTime), 0.0f });
		}
		else
		{
			HeadDirRight = false;
			AddActorLocation({ (-KnockBackX) * Status.Speed * _DeltaTime , 0.0f });
		}

		if (PlayerPos.Y > MonsterPos.Y)
			AddActorLocation({ 0.0f, -(KnockBackY * Status.Speed * _DeltaTime) });
		else
			AddActorLocation({ 0.0f, (-KnockBackY) * Status.Speed * _DeltaTime });
	}
}

void AMonster::ChangeAnimation()
{
	if (true == Alive)
	{
		if (false == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(Status.Name + "_L_Idle"));
		}
		else if (true == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(Status.Name + "_R_Idle"));
		}
	}
	else
	{
		if (false == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(Status.Name + "_L_Die"));
		}
		else if (true == HeadDirRight)
		{
			SpriteRenderer->ChangeAnimation(std::string_view(Status.Name + "_R_Die"));
		}
	}
}

void AMonster::Die()
{	
	DiffPos = PlayerPos - MonsterPos;
	DiffPos = DiffPos / 50.0f;

	Alive = false;
	CollisionComponent->SetActive(false);
	
	Destroy(0.70f);
}

void AMonster::TakeDamage(int _Att)
{
	if (true == CollisionComponent->IsActive())
	{
		CollisionComponent->SetActive(false);

		Status.Hp -= _Att;

		if (0 >= Status.Hp)
		{
			Die();
		}
		else 
		{
			TimeEventer.PushEvent(1.0f, std::bind(&AMonster::EnableCollision, this), false, -1.0f, false);
		}
	}
}

void AMonster::EnableCollision()
{
	CollisionComponent->SetActive(true);
}
