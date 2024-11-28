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

	Level = 1;
	AttackPower = 20.0f;
	Speed = 85.0f;
	Amount = 3;
	Cooldown = 3.0f;
	KnockBack = 1.0f;
	Area = 100.0f;
}

FireWand::~FireWand()
{
}

void FireWand::BeginPlay()
{
	DebugOn();

	AWeapon::BeginPlay();

	player = AInGameMode::Player;
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
		if (Location.X <= -400.0f || Location.X >= 400.0f || Location.Y <= -400.0f || Location.Y >= 400.0f) {
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
}

void FireWand::Action()
{
	AWeapon::Action();
	TimeEventer.PushEvent(Cooldown, std::bind(&FireWand::Attack, this), false, -1.0f, true);
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

void FireWand::Revolution()
{
	AWeapon::Revolution();

	AttackPower += 10.0f;
	Speed += 35.0f;
	Amount -= 1;
	Area += 50.0f;
}

void FireWand::Attack()
{	
	TimeEventer.PushEvent(0.1f, std::bind(&FireWand::ShootFire, this), false, 0.1f * Amount, false);
}

void FireWand::ShootFire()
{
	FVector2D DiffPos = GetActorLocation() - player->GetActorLocation();

	for (int i = 0; i < static_cast<int>(FireWandRenderers.size()); ++i)
	{
		FireWandRenderers[i].second->AddComponentLocation(DiffPos);
	}

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

		/*auto CurrentComponent = CollisionComponents.back();
		CollisionComponents.back()->SetCollisionEnter([this, CurrentComponent](AActor* _ColActor) {			
			AWeapon::CollisionEnter(_ColActor);

			for (int i = 0; i < CollisionComponents.size(); ++i)
			{
				if (CollisionComponents[i] == CurrentComponent)
				{
					if (i < FireWandRenderers.size())
					{
						FireWandRenderers[i].second->Destroy();
						auto iter = FireWandRenderers.begin() + i;
						FireWandRenderers.erase(iter);
					}

					if (i < CollisionComponents.size())
					{
						CollisionComponents[i]->Destroy();
						auto Citer = CollisionComponents.begin() + i;
						CollisionComponents.erase(Citer);
					}
				}
			}			
		});*/
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
	_Renderer->SetSpriteScale(Area / 100.0f);
	_Renderer->SetOrder(ERenderOrder::WEAPON);
	_Renderer->SetComponentLocation(_Pos * player->GetPlayerScale());
}
