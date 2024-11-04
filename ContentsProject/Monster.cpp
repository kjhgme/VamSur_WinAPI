#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/SpriteRenderer.h>

AMonster::AMonster()
{
	MonsterInit({ 100, 0 });
}

AMonster::~AMonster()
{
}

void AMonster::BeginPlay()
{
	SpriteSetting();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMonster::MonsterInit(FVector2D _pos)
{
	SetActorLocation(_pos);
}

void AMonster::SpriteSetting()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bat1_L", 0);
	SpriteRenderer->SetComponentScale({ 64, 64 });

	SpriteRenderer->CreateAnimation("Bat1_L_Idle", "Bat1_L", 0, 0, 0.15f);
	SpriteRenderer->ChangeAnimation("Bat1_L_Idle");
}
