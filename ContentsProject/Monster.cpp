#include "PreCompile.h"
#include "Monster.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include "Player.h"
#include "ExpItem.h"
#include "TextBox.h"
#include "InGameUI.h"
#include "DropItem.h"

UEngineRandom MRandomGenerator;

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	DamageText = GetWorld()->SpawnActor<ATextBox>();
	DamageText->InitOrder(static_cast<int>(ERenderOrder::UI) + 1);
	DamageText->SetTextScale(12);
	DamageText->SetText("", "DamageNum");
	DamageText->SetActorLocation(UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize().Half());
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
	scale.Y = scale.X;

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({ 0.0f, 0.0f });
	CollisionComponent->SetComponentScale(scale);
	CollisionComponent->SetCollisionGroup(ECollisionGroup::MonsterBody);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	CollisionComponent->SetCollisionStay(std::bind(&AMonster::CollisionStay, this, std::placeholders::_1));
}

void AMonster::SetMonsterPos(FVector2D _pos)
{
	SetActorLocation(_pos);
}

void AMonster::ChasePlayer(float _DeltaTime)
{	
	if (true == Alive && true == Hitable)
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
	else if (true == Alive && false == Hitable)
	{
		if (PlayerPos.X > MonsterPos.X)
		{
			AddActorLocation({ -(KnockbackAmount * Status.Speed * _DeltaTime), 0.0f });
		}
		else
		{
			AddActorLocation({ KnockbackAmount * Status.Speed * _DeltaTime , 0.0f });
		}

		if (PlayerPos.Y > MonsterPos.Y)
			AddActorLocation({ 0.0f, -(KnockbackAmount * Status.Speed * _DeltaTime) });
		else
			AddActorLocation({ 0.0f, KnockbackAmount * Status.Speed * _DeltaTime });
	}
	else 
	{
		KnockBack.X = UEngineMath::Clamp(DiffPos.X, -2.0f, 2.0f);
		KnockBack.Y = UEngineMath::Clamp(DiffPos.Y, -2.0f, 2.0f);

		if (PlayerPos.X > MonsterPos.X)
		{
			HeadDirRight = true;
			AddActorLocation({ -(KnockBack.X * Status.Speed * _DeltaTime), 0.0f });
		}
		else
		{
			HeadDirRight = false;
			AddActorLocation({ (-KnockBack.X) * Status.Speed * _DeltaTime , 0.0f });
		}

		if (PlayerPos.Y > MonsterPos.Y)
			AddActorLocation({ 0.0f, -(KnockBack.Y * Status.Speed * _DeltaTime) });
		else
			AddActorLocation({ 0.0f, (-KnockBack.Y) * Status.Speed * _DeltaTime });
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
	Alive = false;
	CollisionComponent->SetActive(false);

	SpawnExpItem();
	AInGameUI::KillAndGold->AddKillCount();
	
	Destroy(0.70f);
}

void AMonster::TakeDamage(float _Att, float _KnockBack)
{
	if (true == CollisionComponent->IsActive())
	{
		DiffPos = PlayerPos - MonsterPos;

		TextFadeValue = 1.0f;
		DamageText->AddActorLocation(-DiffPos);
		DamageText->SetText(std::to_string(static_cast<int>(_Att)), "DamageNum");
		TimeEventer.PushEvent(0.5f, std::bind(&AMonster::TextFadeOut, this), true, -1.0f, false);

		DiffPos = DiffPos / 50.0f;

		Status.Hp -= _Att;

		if (0 >= Status.Hp)
		{
			Die();
		}
		else 
		{
			KnockbackAmount = Status.KnockBack * _KnockBack;
			KnockbackAmount = UEngineMath::ClampMax(KnockbackAmount, Status.KBMax);
			Hitable = false;
			TimeEventer.PushEvent(0.12f, std::bind(&AMonster::KnockbackEnd, this), false, -1.0f, false);
			
			CollisionComponent->SetActive(true);
			TimeEventer.PushEvent(1.0f, std::bind(&AMonster::EnableCollision, this), false, -1.0f, false);
		}
	}
}

void AMonster::EnableCollision()
{
	CollisionComponent->SetActive(true);
}

void AMonster::CollisionStay(AActor* _ColActor)
{
	FVector2D OtherPos = _ColActor->GetActorLocation();
	FVector2D Offset = MonsterPos - OtherPos;

	float ClampedX = UEngineMath::Clamp(Offset.X, -0.1f, 0.1f);
	float ClampedY = UEngineMath::Clamp(Offset.Y, -0.1f, 0.1f);

	AddActorLocation({ ClampedX, ClampedY });
	_ColActor->AddActorLocation({ -ClampedX, -ClampedY });
}

void AMonster::SpawnExpItem()
{
	float time = UEngineAPICore::GetCore()->GetDeltaTime();
	__int64 UniqueSeed = static_cast<__int64>((MonsterPos.X * 1000 + MonsterPos.Y * 1000) + time * 10000);
	MRandomGenerator.SetSeed(UniqueSeed);
	
	if (MRandomGenerator.RandomInt(0, 1) == 1)
	{
		AExpItem* newExpItem = GetWorld()->SpawnActor<AExpItem>();
		newExpItem->InitDropItem(MonsterPos);
		newExpItem->SetExp(Status.XP);
	}
}

void AMonster::KnockbackEnd()
{
	Hitable = true;
}

void AMonster::TextFadeOut()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	TextFadeValue += DeltaTime * 2.0f * TextFadeDir;

	for (int i = 0; i <	DamageText->GetTextRenders().size(); ++i)
	{
		DamageText->GetTextRenders()[i]->SetAlphafloat(TextFadeValue);
	}
}
