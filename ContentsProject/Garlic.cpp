#include "PreCompile.h"
#include "Garlic.h"
#include "ContentsEnum.h"

#include "EngineCore/EngineAPICore.h"

Garlic::Garlic()
{
	WeaponType = EWeaponType::Garlic;

	LevelDescriptions = {
		{1, "Damages nearby enemies.\nReduces resistance to knockback."},
		{2, "Base Area up by 40%.\nBase Damage up by 2."},
		{3, "Cooldown reduced by 0.1 seconds.\nBase Damage up by 1."},
		{4, "Base Area up by 20%.\nBase Damage up by 1."},
		{5, "Cooldown reduced by 0.1 seconds.\nBase Damage up by 2."},
		{6, "Base Area up by 20%.\nBase Damage up by 1."},
		{7, "Cooldown reduced by 0.1 seconds.\nBase Damage up by 1."},
		{8, "Base Area up by 20%.\nBase Damage up by 1."},
	};
}

Garlic::~Garlic()
{
}

void Garlic::BeginPlay()
{
	AWeapon::BeginPlay();

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WEAPON);
		SpriteRenderer->SetSprite("Garlic", 0);
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetAlphafloat(0.1f);
	}

	InitCollision();

	Level = 1;
	AttackPower = 10;
	KnockBack = 1;
}

void Garlic::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);

	FadeValue += _DeltaTime * 0.5f * FadeDir;
	FadeValue = UEngineMath::Clamp(FadeValue, 0.0f, 0.2f);
	SpriteRenderer->SetAlphafloat(FadeValue);
}

void Garlic::InitCollision()
{
	FVector2D scale = SpriteRenderer->GetComponentScale();
	scale.X = scale.Y;

	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());
	CollisionComponents[0]->SetComponentLocation({ 0.0f, 0.0f });
	CollisionComponents[0]->SetComponentScale(scale);
	CollisionComponents[0]->SetCollisionGroup(ECollisionGroup::WeaponBody);
	CollisionComponents[0]->SetCollisionType(ECollisionType::CirCle);

	CollisionComponents[0]->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
	CollisionComponents[0]->SetCollisionStay(std::bind(&AWeapon::CollisionStay, this, std::placeholders::_1));
	CollisionComponents[0]->SetCollisionEnd(std::bind(&AWeapon::CollisionEnd, this, std::placeholders::_1));
}

void Garlic::Action()
{
	TimeEventer.PushEvent(0.5f, std::bind(&Garlic::FadeChange, this));
}

void Garlic::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Area += 40.0f;
		AttackPower += 2;
		break;
	case 3:
		Cooldown += 0.1f;
		AttackPower += 1;
		break;
	case 4:
		Area += 20.0f;
		AttackPower += 1;
		break;
	case 5:
		Cooldown += 0.1f;
		AttackPower += 2;
		break;
	case 6:
		Area += 20.0f;
		AttackPower += 1;
		break;
	case 7:
		Cooldown += 0.1f;
		AttackPower += 1;
		break;
	case 8:
		Area += 20.0f;
		AttackPower += 1;
		break;
	}
}

void Garlic::Attack()
{
}

void Garlic::FadeChange()
{
	FadeDir = -FadeDir;
}
