#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineAPICore.h>

#include "Bullet.h"

APlayer::APlayer()
{
	SetActorLocation({ 0, 0 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Antonio", 4);
	SpriteRenderer->SetComponentScale({ 64, 64 });

	SpriteRenderer->CreateAnimation("Idle_L", "Antonio", 0, 0, 0.15f);
	SpriteRenderer->CreateAnimation("Idle_R", "Antonio", 4, 4, 0.15f);
	SpriteRenderer->CreateAnimation("Move_L", "Antonio", 0, 3, 0.15f);
	SpriteRenderer->CreateAnimation("Move_R", "Antonio", 4, 7, 0.15f);
	SpriteRenderer->ChangeAnimation("Idle_R");

	std::string Name = SpriteRenderer->GetCurSpriteName();
}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	PlayerMove(_DeltaTime);
}

void APlayer::PlayerMove(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		HeadDirRight = true;
		SpriteRenderer->ChangeAnimation("Move_R");

		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		HeadDirRight = false;
		SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Move_R");
		else
			SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Move_R");
		else
			SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}
	if (true == UEngineInput::GetInst().IsFree('A') &&
		true == UEngineInput::GetInst().IsFree('D') &&
		true == UEngineInput::GetInst().IsFree('W') &&
		true == UEngineInput::GetInst().IsFree('S'))
	{
		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Idle_R");
		else
			SpriteRenderer->ChangeAnimation("Idle_L");
	}
}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}