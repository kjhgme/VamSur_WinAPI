#include "PreCompile.h"
#include "Monster.h"

#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

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

	ChasePlayer(_DeltaTime);
}

void AMonster::MonsterInit(FVector2D _pos)
{
	SetActorLocation(_pos);
}

void AMonster::SpriteSetting()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Bat1_L", 0);
	SpriteRenderer->SetComponentScale({ 38, 42 });

	SpriteRenderer->CreateAnimation("Bat1_L_Idle", "Bat1_L", 0, 4, 0.1f);
	SpriteRenderer->ChangeAnimation("Bat1_L_Idle");
}

void AMonster::ChasePlayer(float _DeltaTime)
{
	FVector2D MonsterPos = GetActorLocation();
	FVector2D PlayerPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	if (PlayerPos.X > MonsterPos.X)
		AddActorLocation({ Speed * 100.0f * _DeltaTime, 0.0f });
	else
		AddActorLocation({ -(Speed * 100.0f * _DeltaTime), 0.0f });


	if (PlayerPos.Y > MonsterPos.Y)
		AddActorLocation({ 0.0f, Speed * 100.0f * _DeltaTime });
	else
		AddActorLocation({ 0.0f, -(Speed * 100.0f * _DeltaTime) });

}
