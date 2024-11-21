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
		{4, "Base Area up by 10%.\nBase Damage up by 5."},
		{5, "Base Damage up by 5."},
		{6, "Base Area up by 10%.\nBase Damage up by 5."},
		{7, "Base Damage up by 5."},
		{8, "Base Damage up by 5."},
	};
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
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetAlphaChar(0);
	}

	InitCollision();

	Level = 1;
	AttackPower = 10;
	KnockBack = 1;

	DebugOn();
}

void Whip::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);
}

void Whip::InitCollision()
{
	AWeapon::InitCollision();

	CollisionComponents.resize(4);

	for (int i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i] = CreateDefaultSubObject<U2DCollision>();
		CollisionComponents[i]->SetComponentLocation({ 40.0f + (i * 30.0f), -10.0f });
		// CollisionComponents[i]->SetComponentLocation({ 0, 0 });
		CollisionComponents[i]->SetComponentScale({ 40.0f, 40.0f });
		CollisionComponents[i]->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents[i]->SetCollisionType(ECollisionType::CirCle);


		CollisionComponents[i]->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
		CollisionComponents[i]->SetCollisionStay(std::bind(&AWeapon::CollisionStay, this, std::placeholders::_1));
		CollisionComponents[i]->SetCollisionEnd(std::bind(&AWeapon::CollisionEnd, this, std::placeholders::_1));
	}
}

void Whip::Action()
{
	TimeEventer.PushEvent(2.0f, std::bind(&Whip::Attack, this), false, -1.0f, true);
}

void Whip::ChangeHeadDir()
{
	AWeapon::ChangeHeadDir();

	if (true == HeadDirRight)
	{
		SpriteRenderer->SetSprite("Whip", 0);
		SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });

		for (int i = 0; i < CollisionComponents.size(); ++i)
		{
			CollisionComponents[i]->SetComponentLocation({ 40.0f + (i * 30.0f), -10.0f });
		}
	}
	else
	{
		SpriteRenderer->SetSprite("Whip", 1);
		SpriteRenderer->SetComponentLocation({ -110.0f, -10.0f });

		for (int i = 0; i < CollisionComponents.size(); ++i)
		{
			CollisionComponents[i]->SetComponentLocation({ -40.0f + (i * -30.0f), -10.0f });
		}
	}
}

void Whip::Attack()
{
	for (int i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i]->SetActive(true);
	}

	FadeValue = 1.0f;
	TimeEventer.PushEvent(0.5f, std::bind(&Whip::FadeOut, this), true);
}

void Whip::FadeOut()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 2.0f * FadeDir;
	SpriteRenderer->SetAlphafloat(FadeValue);

	if (0 >= FadeValue)
	{
		for (int i = 0; i < CollisionComponents.size(); ++i)
		{
			CollisionComponents[i]->SetActive(false);
		}
	}
}
