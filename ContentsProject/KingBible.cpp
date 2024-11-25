#include "PreCompile.h"
#include "KingBible.h"
#include "ContentsEnum.h"

KingBible::KingBible()
{
	WeaponType = EWeaponType::KingBible;

	LevelDescriptions = {
		{1, "Orbits around the character."},
		{2, "Fires 1 more projectile."},
		{3, "Base Area up by 25%.\nBase Speed up by 30%."},
		{4, "Base Damage up by 10."},
		{5, "Fires 1 more projectile."},
		{6, "Base Area up by 25%.\nBase Speed up by 30%."},
		{7, "Base Damage up by 10."},
		{8, "Fires 1 more projectile."},
	};
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

	InitCollision();

	Level = 1;
	AttackPower = 10;
	KnockBack = 1;
}

void KingBible::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);

	CurAngle += MoveSpeed * _DeltaTime;
	Pos = CalculateCircularPosition(FVector2D::ZERO, 80.0f, CurAngle);
	
	for (size_t i = 0; i < BibleRenderers.size(); ++i)
	{
		BibleRenderers[i]->SetComponentLocation(Pos);
	}
	
	for (size_t i = 0; i < CollisionComponents.size(); ++i)
	{
		CollisionComponents[i]->SetComponentLocation(Pos);
	}
}

void KingBible::InitCollision()
{
	FVector2D scale = BibleRenderers[0]->GetComponentScale();
	scale.X = scale.Y;

	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());
	CollisionComponents[0]->SetComponentLocation({0.0f, 0.0f});
	CollisionComponents[0]->SetComponentScale(scale);
	CollisionComponents[0]->SetCollisionGroup(ECollisionGroup::WeaponBody);
	CollisionComponents[0]->SetCollisionType(ECollisionType::CirCle);

	CollisionComponents[0]->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
	CollisionComponents[0]->SetCollisionStay(std::bind(&AWeapon::CollisionStay, this, std::placeholders::_1));
	CollisionComponents[0]->SetCollisionEnd(std::bind(&AWeapon::CollisionEnd, this, std::placeholders::_1));
}

void KingBible::Action()
{
}

FVector2D KingBible::CalculateCircularPosition(const FVector2D& Center, float Radius, float _CurAngle)
{
	float AngleInRadians = _CurAngle * (3.1415f / 180.0f);

	float X = Center.X + Radius * cos(AngleInRadians);
	float Y = Center.Y + Radius * sin(AngleInRadians);

	return FVector2D(X, Y);
}
