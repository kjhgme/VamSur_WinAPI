#include "PreCompile.h"
#include "FireWand.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include "InGameMode.h"

UEngineRandom FWRandomGenerator;

FireWand::FireWand()
{
	WeaponType = EWeaponType::FireWand;

	LevelDescriptions = {
		{1, "Fires at a random enemy,\ndeals heavy damage."},
		{2, "Base Damage up by 10."},
		{3, "Base Damage up by 10.\nBase Speed up by 20%"},
		{4, "Base Damage up by 10."},
		{5, "Base Damage up by 10.\nBase Speed up by 20%"},
		{6, "Base Damage up by 10."},
		{7, "Base Damage up by 10.\nBase Speed up by 20%"},
		{8, "Base Damage up by 10."},
	};
}

FireWand::~FireWand()
{
}

void FireWand::BeginPlay()
{
	DebugOn();

	AWeapon::BeginPlay();

	player = AInGameMode::Player;

	Level = 1;
	AttackPower = 20;
	Speed = 75.0f;
	Amount = 3;
	Cooldown = 3.0f;
	KnockBack = 1;
}

void FireWand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < FireWandRenderers.size(); ++i)
	{
		auto& Renderer = FireWandRenderers[i];
		auto OffsetIt = FWMoveOffsets.find(Renderer.first);

		if (OffsetIt != FWMoveOffsets.end()) {
			Renderer.second->AddComponentLocation(OffsetIt->second * (Speed / 100.0f));
		}

		const FVector2D Location = Renderer.second->GetComponentLocation();
		if (Location.X <= -500.0f || Location.X >= 500.0f || Location.Y <= -500.0f || Location.Y >= 500.0f) {
			PopFireWand();
			continue;
		}

		if (i < CollisionComponents.size()) {
			CollisionComponents[i]->SetComponentLocation(Location);
		}
	}
}

void FireWand::InitCollision()
{
	AWeapon::InitCollision();
}

void FireWand::Action()
{
	TimeEventer.PushEvent(Cooldown, std::bind(&FireWand::Attack, this), false, -1.0f, false);
}

void FireWand::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		AttackPower += 10;
		break;
	case 3:
		AttackPower += 10;
		Speed += 20.0f;
		break;
	case 4:
		AttackPower += 10;
		break;
	case 5:
		AttackPower += 10;
		Speed += 20.0f;
		break;
	case 6:
		AttackPower += 10;
		break;
	case 7:
		AttackPower += 10;
		Speed += 20.0f;
		break;
	case 8:
		AttackPower += 10;
		break;
	}
}

void FireWand::Attack()
{
	for(int i = 0 ; i < Amount; ++i)
	{
		TimeEventer.PushEvent(Cooldown, std::bind(&FireWand::FireBurst, this), false, -1.0f, true);
	}
}

void FireWand::FireBurst()
{
	SetActorLocation(player->GetActorLocation());

	FireWandRenderers.push_back(std::make_pair("Fire_RC.png", CreateDefaultSubObject<USpriteRenderer>()));
	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());

	{
		int Num = FWRandomGenerator.RandomInt(0, 7);

		for (const auto& Condition : FireWandDirMapping)
		{
			if (Num == Condition.RanAngle)
			{
				FireWandRenderers.back().first = Condition.SpriteName;
				SetFireRendererProperties(FireWandRenderers.back().second, Condition.SpriteName, Condition.Pos);

				CollisionComponents.back()->SetComponentLocation(Condition.Pos * player->GetPlayerScale());

				break;
			}
		}
	}
	{
		FVector2D scale = FireWandRenderers.back().second->GetComponentScale();
		scale.Y = scale.X;
		CollisionComponents.back()->SetComponentScale(scale);
		CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);
		CollisionComponents.back()->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
	}
}

void FireWand::PopFireWand()
{
	if (!FireWandRenderers.empty())
	{
		FireWandRenderers.front().second->Destroy();
		FireWandRenderers.pop_front();
	}

	if (!CollisionComponents.empty())
	{
		CollisionComponents.front()->Destroy();
		CollisionComponents.pop_front();
	}
}

void FireWand::SetFireRendererProperties(USpriteRenderer* _Renderer, const std::string& _SpriteName, FVector2D _Pos)
{
	_Renderer->SetSprite(_SpriteName);
	_Renderer->SetSpriteScale(1.0f);
	_Renderer->SetOrder(ERenderOrder::WEAPON);
	_Renderer->SetComponentLocation(_Pos * player->GetPlayerScale());
}
