#include "PreCompile.h"
#include "Player.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>

#include "CharactersStatus.h"

APlayer::APlayer()
{
	SetActorLocation({ 10, 10 });
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

	InitCreatePlayerAnim();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	PlayerMove(_DeltaTime);
}

void APlayer::PlayerInit(std::string_view _name)
{
	InitSprite(_name);
	InitPlayerStatus(_name);
}

void APlayer::InitPlayerStatus(std::string_view _name)
{
	if (_name == "Antonio") {
		PlayerStatus.Name = AntonioStatus.Name;
		PlayerStatus.Health = AntonioStatus.Health;
		PlayerStatus.Armor = AntonioStatus.Armor;
		PlayerStatus.Might = AntonioStatus.Might;
		PlayerStatus.Speed = AntonioStatus.Speed;
	}
	else if (_name == "Imelda") {
		PlayerStatus.Name = ImeldaStatus.Name;
		PlayerStatus.Health = ImeldaStatus.Health;
		PlayerStatus.Armor = ImeldaStatus.Armor;
		PlayerStatus.Might = ImeldaStatus.Might;
		PlayerStatus.Speed = ImeldaStatus.Speed;
	}
}

void APlayer::InitSprite(std::string_view _name)
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite(_name, 4);
	SpriteRenderer->SetSpriteScale(2.0f);
}

void APlayer::InitCreatePlayerAnim()
{
	std::string name = PlayerStatus.Name;
	if (!(name.empty()))
	{
		SpriteRenderer->CreateAnimation("Idle_L", name, 0, 0, 0.15f);
		SpriteRenderer->CreateAnimation("Idle_R", name, 4, 4, 0.15f);
		SpriteRenderer->CreateAnimation("Move_L", name, 0, 3, 0.15f);
		SpriteRenderer->CreateAnimation("Move_R", name, 4, 7, 0.15f);
	}
}

void APlayer::PlayerMove(float _DeltaTime)
{
	UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->SetActorLocation(this->GetActorLocation());
	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		HeadDirRight = true;
		SpriteRenderer->ChangeAnimation("Move_R");

		AddActorLocation(FVector2D::RIGHT * _DeltaTime * PlayerStatus.Speed);
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		HeadDirRight = false;
		SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::LEFT * _DeltaTime * PlayerStatus.Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Move_R");
		else
			SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::DOWN * _DeltaTime * PlayerStatus.Speed);
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Move_R");
		else
			SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::UP * _DeltaTime * PlayerStatus.Speed);
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