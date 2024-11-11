#include "PreCompile.h"
#include "Bat1.h"

Bat1::Bat1()
{
}

Bat1::~Bat1()
{
}

void Bat1::InitSprite()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bat1_L", 0);

	SpriteRenderer->SetSpriteScale(1.0f);
}

void Bat1::InitMonsterStatus()
{
	MonsterStatus.Name = Bat1Status.Name;
	MonsterStatus.Health = Bat1Status.Health;
	MonsterStatus.Power = Bat1Status.Power;
	MonsterStatus.Speed = Bat1Status.Speed;
	MonsterStatus.KnockBack = Bat1Status.KnockBack;
	MonsterStatus.KBMax = Bat1Status.KBMax;
	MonsterStatus.XP = Bat1Status.XP;
}
