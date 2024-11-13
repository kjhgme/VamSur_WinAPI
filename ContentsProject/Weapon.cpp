#include "PreCompile.h"
#include "Weapon.h"

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
