#include "PreCompile.h"
#include "Weapon.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include "Monster.h"

void AWeapon::BeginPlay()
{
	DebugOn();

	PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
}

void AWeapon::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	PlayerPos = GetWorld()->GetMainPawn()->GetActorLocation();
	SetActorLocation(PlayerPos);
}

void AWeapon::Action()
{
}

void AWeapon::ChangeHeadDir()
{
	HeadDirRight  = !HeadDirRight;
}

void AWeapon::LevelUp()
{
	Level++;
}

void AWeapon::Revolution()
{
	bIsEvolved = true;
}

void AWeapon::CollisionEnter(AActor* _ColActor)
{
	AMonster* Monster = static_cast<AMonster*>(_ColActor);
	if (true == Monster->CollisionComponent->IsActive())
	{
		Monster->TakeDamage(AttackPower, KnockBack);
	}

	HitSoundPlayer = UEngineSound::Play("Hit.wav");
}

void AWeapon::CollisionStay(AActor* _ColActor)
{
	/*AMonster* Monster = static_cast<AMonster*>(_ColActor);
	if (true == Monster->CollisionComponent->IsActive())
	{
		Monster->TakeDamage(AttackPower);
	}*/
}

void AWeapon::CollisionEnd(AActor* _ColActor)
{
}
