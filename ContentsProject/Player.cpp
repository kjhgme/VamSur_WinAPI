#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"

#include <unordered_map>

#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include "WeaponManager.h"
#include "PlayerHpUI.h"
#include "InGameUI.h"
#include "Monster.h"

CharacterStatus APlayer::PlayerStatus;

APlayer::APlayer()
{
	SetActorLocation( FVector2D::ZERO );
	InitCollision();

	DebugOn();
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

	PlayerHpUI* HpUI = GetWorld()->SpawnActor<PlayerHpUI>();
	WeaponManager = GetWorld()->SpawnActor<AWeaponManager>();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	PlayerMove(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineDebug::SwitchIsDebug();
	}
	if (true == UEngineInput::GetInst().IsDown('L'))
	{
		// AddExp(5.0f);
		LevelUp();
		PlayerStatus.Exp = 0.0f;
	}
	if (true == UEngineInput::GetInst().IsDown('P'))
	{
		UEngineAPICore::GetCore()->GetTimer().ToggleTime();
	}
}

void APlayer::PlayerInit(std::string_view _name)
{
	InitSprite(_name);
	InitPlayerStatus(_name);
}

void APlayer::InitPlayerStatus(std::string_view _name)
{
	static const std::unordered_map<std::string_view, const CharacterStatus*> characterStatusMap = {
		{"Antonio", &AntonioStatus},
		{"Imelda", &ImeldaStatus}
	};

	auto it = characterStatusMap.find(_name);
	if (it != characterStatusMap.end()) {
		PlayerStatus = *(it->second);
	}
	else {
		PlayerStatus = CharacterStatus();
	}
}

void APlayer::InitSprite(std::string_view _name)
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite(_name, 4);
		SpriteRenderer->SetSpriteScale(1.0f);
	}

	{
		BloodRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BloodRenderer->SetSprite("Blood", 3);
		BloodRenderer->SetSpriteScale(1.0f);
	}
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

	{
		BloodRenderer->CreateAnimation("TakeDamage", "Blood", 0, 2, 0.1f, true);
		BloodRenderer->CreateAnimation("NoDamage", "Blood", 3, 3);
	}
}

void APlayer::InitCollision()
{
	{
		CollisionComponent = CreateDefaultSubObject<U2DCollision>();
		CollisionComponent->SetComponentLocation({ 0.0f, 0.0f });
		CollisionComponent->SetComponentScale({ 60.0f, 60.0f });
		CollisionComponent->SetCollisionGroup(ECollisionGroup::PlayerBody);
		CollisionComponent->SetCollisionType(ECollisionType::CirCle);

		CollisionComponent->SetCollisionEnter(std::bind(&APlayer::CollisionEnter, this, std::placeholders::_1));
		CollisionComponent->SetCollisionStay(std::bind(&APlayer::CollisionStay, this, std::placeholders::_1));
		CollisionComponent->SetCollisionEnd(std::bind(&APlayer::CollisionEnd, this, std::placeholders::_1));
	}
}

void APlayer::PlayerMove(float _DeltaTime)
{
	UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->SetActorLocation(this->GetActorLocation());
	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		HeadDirStationary = false;
		if (false == HeadDirRight)
		{
			HeadDirRight = true;
			WeaponManager->ChangeDir();
		}
		SpriteRenderer->ChangeAnimation("Move_R");

		AddActorLocation(FVector2D::RIGHT * _DeltaTime * PlayerStatus.Speed);
	}
	else if (true == UEngineInput::GetInst().IsPress('A'))
	{
		HeadDirStationary = false;

		if (true == HeadDirRight)
		{
			HeadDirRight = false;
			WeaponManager->ChangeDir();
		}
		SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::LEFT * _DeltaTime * PlayerStatus.Speed);
	}
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		HeadDirBottom = true;

		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Move_R");
		else
			SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::DOWN * _DeltaTime * PlayerStatus.Speed);
	}
	else if (true == UEngineInput::GetInst().IsPress('W'))
	{
		HeadDirTop = true;

		if (true == HeadDirRight)
			SpriteRenderer->ChangeAnimation("Move_R");
		else
			SpriteRenderer->ChangeAnimation("Move_L");

		AddActorLocation(FVector2D::UP * _DeltaTime * PlayerStatus.Speed);
	}
	if (true == UEngineInput::GetInst().IsUp('S'))
	{
		HeadDirBottom = false;
	}
	if (true == UEngineInput::GetInst().IsUp('W'))
	{
		HeadDirTop = false;
	}
	if (true == UEngineInput::GetInst().IsFree('A') &&
		true == UEngineInput::GetInst().IsFree('D') &&
		true == UEngineInput::GetInst().IsPress('S'))
	{
		HeadDirStationary = true;
	}
	if (true == UEngineInput::GetInst().IsFree('A') &&
		true == UEngineInput::GetInst().IsFree('D') &&
		true == UEngineInput::GetInst().IsPress('W'))
	{
		HeadDirStationary = true;
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

void APlayer::CollisionEnter(AActor* _ColActor)
{
	AMonster* monster = static_cast<AMonster*>(_ColActor);
	PlayerStatus.Hp -= monster->GetAttPower() - PlayerStatus.Armor;

	if (PlayerStatus.Hp <= 0)
	{
		Die();
	}
	BloodRenderer->ChangeAnimation("TakeDamage");
}

void APlayer::CollisionStay(AActor* _ColActor)
{
	TakeDamage(_ColActor);
}

void APlayer::CollisionEnd(AActor* _ColActor)
{
	CollisionStayTimers.erase(_ColActor);

	if (0 == CollisionStayTimers.size())
	{
		BloodRenderer->ChangeAnimation("NoDamage");
	}
}

void APlayer::TakeDamage(AActor* _ColActor)
{
	float Time = UEngineAPICore::GetCore()->GetDeltaTime();
	AMonster* monster = static_cast<AMonster*>(_ColActor);

	if (CollisionStayTimers.find(_ColActor) == CollisionStayTimers.end())
	{
		CollisionStayTimers[_ColActor] = 0.0f;
	}

	CollisionStayTimers[_ColActor] += Time;

	if (CollisionStayTimers[_ColActor] >= 1.0f)
	{
		PlayerStatus.Hp -= monster->GetAttPower() - PlayerStatus.Armor;

		CollisionStayTimers[_ColActor] = 0.0f;
	}

	if (PlayerStatus.Hp <= 0)
	{
		Die();
	}
}

void APlayer::Die()
{

}

void APlayer::AddExp(float _add)
{
	PlayerStatus.Exp += _add;

	if (PlayerStatus.Exp >= PlayerStatus.MaxExp)
	{
		LevelUp();
	}
}

void APlayer::LevelUp()
{
	UEngineAPICore::GetCore()->GetTimer().ToggleTime();

	PlayerStatus.Exp -= PlayerStatus.MaxExp;

	UpdateMaxExp();
	PlayerStatus.Level++;

	std::vector<std::pair<EWeaponType, WeaponLevelData>> RandomWeapons = WeaponManager->GetRandWeapons();

	AInGameUI::ExpBar->SetPlayerLevel();
	AInGameUI::LevelUpPanel->ChangeTextBox(RandomWeapons);
	AInGameUI::LevelUpPanel->SetActive();
}

void APlayer::UpdateMaxExp()
{
	if (PlayerStatus.Level < 20)
	{
		PlayerStatus.MaxExp += 10.0f;
	}
	else if (PlayerStatus.Level <= 40)
	{
		PlayerStatus.MaxExp += 13.0f;
	}
	else
	{
		PlayerStatus.MaxExp += 16.0f;
	}

	if (PlayerStatus.Level == 20)
	{
		PlayerStatus.MaxExp += 600.0f;  
	}
	else if (PlayerStatus.Level == 40)
	{
		PlayerStatus.MaxExp += 2400.0f; 
	}
}

void APlayer::AddHp(float _add)
{
	PlayerStatus.Hp += _add;
	PlayerStatus.Hp = UEngineMath::ClampMax(PlayerStatus.Hp, PlayerStatus.MaxHp);
}
