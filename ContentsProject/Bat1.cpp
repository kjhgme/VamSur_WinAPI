#include "PreCompile.h"
#include "Bat1.h"

Bat1::Bat1()
{
	SetSprite();
}

Bat1::~Bat1()
{
}

void Bat1::SetSprite()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bat1_L", 0);
	SpriteRenderer->SetComponentScale({ 38, 42 });

	SpriteRenderer->CreateAnimation("Bat1_L_Idle", "Bat1_L", 0, 4, 0.1f);
	SpriteRenderer->ChangeAnimation("Bat1_L_Idle");
}

void Bat1::SetMonsterStatus()
{
	MonsterStatus.Health = BatStatus.Health;
	MonsterStatus.Power = BatStatus.Power;
	MonsterStatus.Speed = BatStatus.Speed;
	MonsterStatus.KnockBack = BatStatus.KnockBack;
	MonsterStatus.KBMax = BatStatus.KBMax;
	MonsterStatus.XP = BatStatus.XP;
}
