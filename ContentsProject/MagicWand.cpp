#include "PreCompile.h"
#include "MagicWand.h"
#include "ContentsEnum.h"

MagicWand::MagicWand()
{
	WeaponType = EWeaponType::MagicWand;

	LevelDescriptions = {	
		{1, "Fires at the nearest enemy."},
		{2, "Fires 1 more projectile."},
		{3, "Cooldown reduced by 0.2 seconds."},
		{4, "Fires 1 more projectile."},
		{5, "Base Damage up by 10."},
		{6, "Fires 1 more projectile."},
		{7, "Passes through 1 more enemy."},
		{8, "Base Damage up by 10."},
	};
}

MagicWand::~MagicWand()
{
}

void MagicWand::BeginPlay()
{
	AWeapon::BeginPlay();
	
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WEAPON);
		SpriteRenderer->SetSprite("MagicWand", 0);
		SpriteRenderer->SetComponentLocation({ 50.0f, 50.0f });
		SpriteRenderer->SetSpriteScale(1.0f);
	}

	Level = 1;
	AttackPower = 10;
	KnockBack = 1;
}

void MagicWand::Tick(float _DeltaTime)
{
}

void MagicWand::InitCollision()
{
}

void MagicWand::Action()
{
}
