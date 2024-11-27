#include "PreCompile.h"
#include "KingBible.h"
#include "ContentsEnum.h"

#include "EngineCore/EngineAPICore.h"

KingBible::KingBible()
{
	WeaponType = EWeaponType::KingBible;

	LevelDescriptions = {
		{1, "Orbits around the character."},
		{2, "Fires 1 more projectile."},
		{3, "Base Area up by 25%\nBase Speed up by 30%"},
		{4, "Base Damage up by 10."},
		{5, "Fires 1 more projectile."},
		{6, "Base Area up by 25%\nBase Speed up by 30%"},
		{7, "Base Damage up by 10."},
		{8, "Fires 1 more projectile."},
	};

	Level = 1;
	AttackPower = 10.0f;
	Speed = 100.0f;
	Amount = 1;
	Duration = 3.0f;
	Cooldown = 3.0f;
	KnockBack = 1.0f;
	Area = 100.0f;
}

KingBible::~KingBible()
{
}

void KingBible::BeginPlay()
{
	AWeapon::BeginPlay();

	{
		BibleRenderers.push_back(CreateDefaultSubObject<USpriteRenderer>());
		BibleRenderers[0]->SetOrder(ERenderOrder::WEAPON);
		BibleRenderers[0]->SetSprite("KingBible", 0);
		BibleRenderers[0]->SetSpriteScale(1.0f);
	}

	InitCollision(0);
}

void KingBible::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);

	CurAngle += Speed * _DeltaTime;
	
	for (size_t i = 0; i < BibleRenderers.size(); ++i)
	{
		float RendererAngle = CurAngle + (360.0f / BibleRenderers.size()) * i;
		RendererAngle = fmod(RendererAngle, 360.0f);
		
		Pos = CalculateCircularPosition(FVector2D::ZERO, Area, RendererAngle);

		BibleRenderers[i]->SetComponentLocation(Pos); 
		CollisionComponents[i]->SetComponentLocation(Pos);
				
		FadeValue += _DeltaTime * 3.0f * FadeDir;
		FadeValue = UEngineMath::Clamp(FadeValue, 0.0f, 1.0f);
		BibleRenderers[i]->SetAlphafloat(FadeValue);
	}
}

void KingBible::InitCollision(int _num)
{
	FVector2D scale = BibleRenderers[_num]->GetComponentScale();
	scale.X = scale.Y;

	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());
	CollisionComponents[_num]->SetComponentLocation({0.0f, 0.0f});
	CollisionComponents[_num]->SetComponentScale(scale);
	CollisionComponents[_num]->SetCollisionGroup(ECollisionGroup::WeaponBody);
	CollisionComponents[_num]->SetCollisionType(ECollisionType::CirCle);

	CollisionComponents[_num]->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
	CollisionComponents[_num]->SetCollisionStay(std::bind(&AWeapon::CollisionStay, this, std::placeholders::_1));
	CollisionComponents[_num]->SetCollisionEnd(std::bind(&AWeapon::CollisionEnd, this, std::placeholders::_1));
}

void KingBible::Action()
{
	Attack();
	TimeEventer.PushEvent(Duration + Cooldown, std::bind(&KingBible::Attack, this), false, -1.0f, true);
}

void KingBible::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		AddBible();
		break;
	case 3:
		Area += 25.0f;
		Speed += 30.0f;
		break;
	case 4:
		Duration += 0.5f;
		ChangeDuration();
		AttackPower += 10.0f;
		break;
	case 5:
		AddBible();
		break;
	case 6:
		Area += 25.0f;
		Speed += 30.0f;
		break;
	case 7:
		Duration += 0.5f;
		ChangeDuration();
		AttackPower += 10.0f;
		break;
	case 8:
		AddBible();
		break;
	}
}

void KingBible::Attack()
{
	FadeDir = 1.0f;
		
	for (int i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i]->SetActive(true);
	}	
	
	TimeEventer.PushEvent(1.0f, std::bind(&KingBible::FadeOut, this), true, Duration, false);
}

void KingBible::FadeOut()
{
	FadeDir = -1.0f;
	
	if (0.0f >= FadeValue)
	{
		for (int i = 0; i < CollisionComponents.size(); ++i)
		{
			CollisionComponents[i]->SetActive(false);
		}
	}
}

void KingBible::ChangeDuration()
{
	TimeEventer.ChangeCoolTime(std::bind(&KingBible::Attack, this), Duration + Cooldown);
}

FVector2D KingBible::CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle)
{
	float AngleInRadians = _CurAngle * (3.1415f / 180.0f);

	float X = Center.X + Radius * cos(AngleInRadians);
	float Y = Center.Y + Radius * sin(AngleInRadians);

	return FVector2D(X, Y);
}

void KingBible::AddBible()
{
	Amount++;

	if (2 == Amount)
	{
		{
			BibleRenderers.push_back(CreateDefaultSubObject<USpriteRenderer>());
			BibleRenderers[1]->SetOrder(ERenderOrder::WEAPON);
			BibleRenderers[1]->SetSprite("KingBible", 0);
			BibleRenderers[1]->SetSpriteScale(1.0f);

			InitCollision(1);
		}
	}
	else if (3 == Amount)
	{
		{
			BibleRenderers.push_back(CreateDefaultSubObject<USpriteRenderer>());
			BibleRenderers[2]->SetOrder(ERenderOrder::WEAPON);
			BibleRenderers[2]->SetSprite("KingBible", 0);
			BibleRenderers[2]->SetSpriteScale(1.0f);

			InitCollision(2);
		}
	}
	else if (4 == Amount)
	{
		{
			BibleRenderers.push_back(CreateDefaultSubObject<USpriteRenderer>());
			BibleRenderers[3]->SetOrder(ERenderOrder::WEAPON);
			BibleRenderers[3]->SetSprite("KingBible", 0);
			BibleRenderers[3]->SetSpriteScale(1.0f);

			InitCollision(3);
		}

	}

}
