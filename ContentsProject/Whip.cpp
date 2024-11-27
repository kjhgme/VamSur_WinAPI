#include "PreCompile.h"
#include "Whip.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

Whip::Whip()
{
	WeaponType = EWeaponType::Whip;

	LevelDescriptions = {
		{1, "Attacks horizontally,\npasses through enemies."},
		{2, "Fires 1 more projectile."},
		{3, "Base Damage up by 5."},
		{4, "Base Area up by 10%\nBase Damage up by 5."},
		{5, "Base Damage up by 5."},
		{6, "Base Area up by 10%\nBase Damage up by 5."},
		{7, "Base Damage up by 5."},
		{8, "Base Damage up by 5."},
	};

	Level = 1;
	AttackPower = 10.0f;
	KnockBack = 1.0f;
	Area = 100.0f;
	Amount = 1;
	Cooldown = 1.35f;
}

Whip::~Whip()
{
}

void Whip::BeginPlay()
{
	AWeapon::BeginPlay();

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WEAPON);
		SpriteRenderer->SetSprite("Whip", 0);
		SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });
		SpriteRenderer->SetSpriteScale(Area / 100.0f);
		SpriteRenderer->SetAlphaChar(0);
	}

	InitCollision();
}

void Whip::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);
}

void Whip::InitCollision()
{
	Scale = SpriteRenderer->GetComponentScale();
	Scale.X = Scale.Y;

	CollisionComponents.resize(7);

	for (int i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i] = CreateDefaultSubObject<U2DCollision>();
		CollisionComponents[i]->SetComponentLocation({ 40.0f + (i * Scale.X), -10.0f });
		CollisionComponents[i]->SetComponentScale(Scale);
		CollisionComponents[i]->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents[i]->SetCollisionType(ECollisionType::CirCle);

		CollisionComponents[i]->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
		CollisionComponents[i]->SetCollisionStay(std::bind(&AWeapon::CollisionStay, this, std::placeholders::_1));
		CollisionComponents[i]->SetCollisionEnd(std::bind(&AWeapon::CollisionEnd, this, std::placeholders::_1));
	}
}

void Whip::Action()
{
	TimeEventer.PushEvent(Cooldown, std::bind(&Whip::Attack, this), false, -1.0f, true);
}

void Whip::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Area += 20.0f;
		AddWhip();
		break;
	case 3:
		AttackPower += 5;
		break;
	case 4:
		Area += 10.0f;
		AttackPower += 5;
		break;
	case 5:
		AttackPower += 5;
		break;
	case 6:
		Area += 10.0f;
		AttackPower += 5;
		break;
	case 7:
		AttackPower += 5;
		break;
	case 8:
		AttackPower += 5;
		break;
	}

	SpriteRenderer->SetSpriteScale(1.0f * (Area / 100.0f));
	Scale = SpriteRenderer->GetComponentScale();
	Scale.X = Scale.Y;

	for (int i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i]->SetComponentScale(Scale);
	}
}

void Whip::Revolution()
{
	AWeapon::Revolution();

	AttackPower *= 2.0f;
	Area += 30.f;

	SpriteRenderer->SetSpriteScale(1.0f * (Area / 100.0f));
	Scale = SpriteRenderer->GetComponentScale();
	Scale.X = Scale.Y;

	for (int i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i]->SetComponentScale(Scale);
	}

	SpriteRenderer->SetSprite("Whip", 2);
	SecondRenderer->SetSprite("Whip", 3);
}

void Whip::ChangeHeadDir()
{
	AWeapon::ChangeHeadDir();

	int WeaponsSize = static_cast<int>(CollisionComponents.size());

	if (2 <= Amount)
	{
		if (true == HeadDirRight)
		{
			if (bIsEvolved) {
				SpriteRenderer->SetSprite("Whip", 2);
				SecondRenderer->SetSprite("Whip", 3);
			}
			else {
				SpriteRenderer->SetSprite("Whip", 0);
				SecondRenderer->SetSprite("Whip", 1);
			}

			SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });
			SecondRenderer->SetComponentLocation({ -110.0f, -40.0f });

			for (int i = 0; i < WeaponsSize / 2; ++i)
			{
				CollisionComponents[i]->SetComponentLocation({ 40.0f + (i * Scale.X), -10.0f });
			}
			for (int i = WeaponsSize / 2; i < WeaponsSize; ++i)
			{
				CollisionComponents[i]->SetComponentLocation({ -40.0f + ((i - (WeaponsSize / 2)) * -Scale.X), -40.0f });
			}
		}
		else
		{
			if (bIsEvolved) {
				SpriteRenderer->SetSprite("Whip", 3);
				SecondRenderer->SetSprite("Whip", 2);
			}
			else {
				SpriteRenderer->SetSprite("Whip", 1);
				SecondRenderer->SetSprite("Whip", 0);
			}

			SpriteRenderer->SetComponentLocation({ -110.0f, -10.0f });
			SecondRenderer->SetComponentLocation({ 110.0f, -40.0f });

			for (int i = 0; i < WeaponsSize; ++i)
			{
				CollisionComponents[i]->SetComponentLocation({ -40.0f + (i * -Scale.X), -10.0f });
			}
			for (int i = WeaponsSize / 2; i < WeaponsSize; ++i)
			{
				CollisionComponents[i]->SetComponentLocation({ 40.0f + ((i - WeaponsSize / 2) * Scale.X), -40.0f });
			}
		}
	}
	else 
	{
		if (true == HeadDirRight)
		{
			SpriteRenderer->SetSprite("Whip", 0);
			SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });

			for (int i = 0; i < CollisionComponents.size(); ++i)
			{
				CollisionComponents[i]->SetComponentLocation({ 40.0f + (i * Scale.X), -10.0f });
			}
		}
		else
		{
			SpriteRenderer->SetSprite("Whip", 1);
			SpriteRenderer->SetComponentLocation({ -110.0f, -10.0f });

			for (int i = 0; i < CollisionComponents.size(); ++i)
			{
				CollisionComponents[i]->SetComponentLocation({ -40.0f + (i * -Scale.X), -10.0f });
			}
		}
	}	
}

void Whip::Attack()
{
	if (2 <= Amount)
	{
		for (int i = 0; i < CollisionComponents.size() / 2; ++i)
		{
			CollisionComponents[i]->SetActive(true);
		}

		FadeValue = 1.0f;
		SecondFadeValue = 1.0f;
	}
	else 
	{
		for (int i = 0; i < CollisionComponents.size(); ++i)
		{
			CollisionComponents[i]->SetActive(true);
		}

		FadeValue = 1.0f;
	}

	TimeEventer.PushEvent(0.5f, std::bind(&Whip::FadeOut, this), true, -1.0f, false);
}

void Whip::FadeOut()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 2.0f * FadeDir;
	SpriteRenderer->SetAlphafloat(FadeValue);

	int WeaponsSize = static_cast<int>(CollisionComponents.size());

	if (2 <= Amount)
	{
		if (0 >= FadeValue)
		{
			for (int i = 0; i < WeaponsSize / 2; ++i)
			{
				CollisionComponents[i]->SetActive(false);
			}
			for (int i = WeaponsSize / 2; i < WeaponsSize; ++i)
			{
				CollisionComponents[i]->SetActive(true);
			}

			SecondFadeValue += DeltaTime * 2.0f * FadeDir;
			SecondRenderer->SetAlphafloat(SecondFadeValue);

			if (0 >= SecondFadeValue)
			{
				for (int i = WeaponsSize / 2; i < WeaponsSize; ++i)
				{
					CollisionComponents[i]->SetActive(false);
				}
			}
		}
	}
	else {
		if (0 >= FadeValue)
		{
			for (int i = 0; i < WeaponsSize; ++i)
			{
				CollisionComponents[i]->SetActive(false);
			}
		}
	}
}

void Whip::AddWhip()
{
	Amount += 1;

	{
		SecondRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SecondRenderer->SetOrder(ERenderOrder::WEAPON);
		
		if (true == HeadDirRight)
		{
			SecondRenderer->SetSprite("Whip", 1);
			SecondRenderer->SetComponentLocation({ -110.0f, -40.0f });
		}
		else
		{
			SecondRenderer->SetSprite("Whip", 0);
			SecondRenderer->SetComponentLocation({ 110.0f, -40.0f });
		}
		
		SecondRenderer->SetSpriteScale(Area / 100.0f);
		SecondRenderer->SetAlphaChar(0);
	}
	

	Scale = SecondRenderer->GetComponentScale();
	Scale.X = Scale.Y;

	CollisionComponents.resize(14);

	int ColSize = static_cast<int>(CollisionComponents.size());

	for (int i = (ColSize / 2); i < ColSize; ++i)
	{
		CollisionComponents[i] = CreateDefaultSubObject<U2DCollision>();
		CollisionComponents[i]->SetComponentLocation({ -40.0f + ((i - (ColSize / 2)) * -Scale.X), -40.0f });
		CollisionComponents[i]->SetComponentScale(Scale);
		CollisionComponents[i]->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents[i]->SetCollisionType(ECollisionType::CirCle);

		CollisionComponents[i]->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
		CollisionComponents[i]->SetCollisionStay(std::bind(&AWeapon::CollisionStay, this, std::placeholders::_1));
		CollisionComponents[i]->SetCollisionEnd(std::bind(&AWeapon::CollisionEnd, this, std::placeholders::_1));
	}

}
