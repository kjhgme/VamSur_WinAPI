#include "PreCompile.h"
#include "Weapon.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include "Monster.h"

AWeapon::AWeapon()
{
}

AWeapon::~AWeapon()
{
}

void AWeapon::BeginPlay()
{
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

void AWeapon::CollisionEnter(AActor* _ColActor)
{
	AMonster* Monster = static_cast<AMonster*>(_ColActor);
	if (true == Monster->CollisionComponent->IsActive())
	{
		Monster->TakeDamage(AttackPower);
	}
}

void AWeapon::CollisionStay(AActor* _ColActor)
{
	AMonster* Monster = static_cast<AMonster*>(_ColActor);
	if (true == Monster->CollisionComponent->IsActive())
	{
		Monster->TakeDamage(AttackPower);
	}
}

void AWeapon::CollisionEnd(AActor* _ColActor)
{
}