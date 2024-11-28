#include "PreCompile.h"
#include "MagicWand.h"
#include "ContentsEnum.h"

#include <limits>

#include <EngineBase/EngineRandom.h>
#include <EnginePlatform/EngineSound.h>
#include "InGameMode.h"
#include "Monster.h"

UEngineRandom MWRandomGenerator;

MagicWand::MagicWand()
{
	WeaponType = EWeaponType::MagicWand;

	LevelDescriptions = {	
		{1, "Fires at the nearest enemy."},
		{2, "Fires 1 more projectile."},
		{3, "Cooldown reduced by 0.2 seconds."},
		{4, "Fires 1 more projectile."},
		{5, "Base Damage up by 10."},
		{6, "Fires 1 more projectile."},
		{7, "Cooldown reduced by 0.2 seconds."},
		{8, "Base Damage up by 10."},
	};

	Level += 1;
	AttackPower += 10.0f;
	KnockBack += 1.0f;
	Speed += 100.0f;
	Amount += 1;
	Cooldown += 1.2f;
}

MagicWand::~MagicWand()
{
}

void MagicWand::BeginPlay()
{
	AWeapon::BeginPlay();

	player = AInGameMode::Player;
	MonsterSpawner = AInGameMode::MonsterSpawner;
}

void MagicWand::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < CollisionComponents.size(); ++i)
	{
		auto& Renderer = MagicWandRenderers[i];
		auto OffsetIt = MagicMoveOffsets.find(Renderer.first);

		if (OffsetIt != MagicMoveOffsets.end()) {
			Renderer.second->AddComponentLocation(OffsetIt->second * (Speed / 100.0f));
		}
		if (0 == OffsetIt->second.X)
		{
			Renderer.second->AddComponentLocation({ MWRandomGenerator.Randomfloat(-3.0f, 3.0f), 0.0f });
		}
		else if (0 == OffsetIt->second.Y)
		{
			Renderer.second->AddComponentLocation({ 0.0f, MWRandomGenerator.Randomfloat(-3.0f, 3.0f) });
		}
		else
		{
			Renderer.second->AddComponentLocation({ MWRandomGenerator.Randomfloat(-3.0f, 3.0f), MWRandomGenerator.Randomfloat(-3.0f, 3.0f) });
		}
		const FVector2D Location = Renderer.second->GetComponentLocation();
		if (Location.X <= -1000.0f || Location.X >= 1000.0f || Location.Y <= -1000.0f || Location.Y >= 1000.0f) {
			PopMagicWand();
			continue;
		}

		if (i < CollisionComponents.size()) {
			CollisionComponents[i]->SetComponentLocation(Location);
		}
	}
}

void MagicWand::InitCollision()
{
}

void MagicWand::Action()
{
	AWeapon::Action();
	TimeEventer.PushEvent(Cooldown, std::bind(&MagicWand::Attack, this), false, -1.0f, true);
}

void MagicWand::LevelUp()
{
	AWeapon::LevelUp();

	switch (Level)
	{
	case 2:
		Amount += 1;
		break;
	case 3:
		Cooldown -= 0.2f;
		TimeEventer.ChangeCoolTime(std::bind(&MagicWand::Attack, this), Cooldown);
		break;
	case 4:
		Amount += 1;
		break;
	case 5:
		AttackPower += 10.0f;
		break;
	case 6:
		Amount += 1;
		break;
	case 7:
		Cooldown -= 0.2f;
		TimeEventer.ChangeCoolTime(std::bind(&MagicWand::Attack, this), Cooldown);
		break;
	case 8:
		AttackPower += 10.0f;
		break;
	}
}

void MagicWand::Revolution()
{
	AWeapon::Revolution();

	Cooldown -= 0.5f;
	Speed *= 2.0f;

	TimeEventer.ChangeCoolTime(std::bind(&MagicWand::Attack, this), Cooldown);
}

void MagicWand::Attack()
{
	TimeEventer.PushEvent(0.1f, std::bind(&MagicWand::ShootMagic, this), false, 0.1f * Amount, false);
}

void MagicWand::ShootMagic()
{
	AttackSoundPlayer = UEngineSound::Play("MagicWandSound.wav");

	FVector2D DiffPos = GetActorLocation() - player->GetActorLocation();

	for (int i = 0; i < static_cast<int>(MagicWandRenderers.size()); ++i)
	{
		MagicWandRenderers[i].second->AddComponentLocation(DiffPos);
	}
	
	SetActorLocation(player->GetActorLocation());

	MagicWandRenderers.push_back(std::make_pair(0, CreateDefaultSubObject<USpriteRenderer>()));
	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());

	std::list<AMonster*> Monsters = MonsterSpawner->GetMonsters();

	if (0 < Monsters.size())
	{
		AMonster* ClosestMonster = FindClosestMonster(GetActorLocation(), Monsters);

		FVector2D Direction = FVector2D::NormalizeDirection(GetActorLocation(), ClosestMonster->GetActorLocation());

		{
			for (const auto& Condition : MagicWandDirMapping)
			{
				if (Direction.X >= Condition.DirMinX && Direction.X <= Condition.DirMaxX &&
					Direction.Y >= Condition.DirMinY && Direction.Y <= Condition.DirMaxY)
				{
					MagicWandRenderers.back().first = Condition.SpriteNum;
					SetFireRendererProperties(MagicWandRenderers.back().second, Condition.SpriteNum, Condition.Pos);

					CollisionComponents.back()->SetComponentLocation(Condition.Pos * player->GetPlayerScale());

					break;
				}
			}
		}
		{
			FVector2D scale = MagicWandRenderers.back().second->GetComponentScale();
			scale.Y = scale.X;
			CollisionComponents.back()->SetComponentScale(scale);
			CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
			CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);
			CollisionComponents.back()->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
		}
	}
	else {
		{ 
				MagicWandRenderers.back().first = 0;
				FVector2D Pos = { 1.0f, 0.0f };
				SetFireRendererProperties(MagicWandRenderers.back().second, 0, Pos);

				CollisionComponents.back()->SetComponentLocation(Pos * player->GetPlayerScale());
		}
		{
			FVector2D scale = MagicWandRenderers.back().second->GetComponentScale();
			scale.Y = scale.X;
			CollisionComponents.back()->SetComponentScale(scale);
			CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
			CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);
			CollisionComponents.back()->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
		}
	}

	Monsters.clear();
}

void MagicWand::PopMagicWand()
{
	if (!MagicWandRenderers.empty())
	{
		MagicWandRenderers.front().second->Destroy();
		MagicWandRenderers.pop_front();
	}

	if (!CollisionComponents.empty())
	{
		CollisionComponents.front()->Destroy();
		CollisionComponents.pop_front();
	}
}

void MagicWand::SetFireRendererProperties(USpriteRenderer* _Renderer, int _SpriteNum, FVector2D _Pos)
{
	_Renderer->SetSprite("MagicWand", _SpriteNum);
	_Renderer->SetSpriteScale(1.0f);
	_Renderer->SetOrder(ERenderOrder::WEAPON);
	_Renderer->SetComponentLocation(_Pos * player->GetPlayerScale());
}

AMonster* MagicWand::FindClosestMonster(const FVector2D& ActorLocation, const std::list<AMonster*>& Monsters)
{
	AMonster* ClosestMonster = nullptr;
	float MinDistance = FLT_MAX;

	for (AMonster* Monster : Monsters)
	{
		if (Monster == nullptr)
			continue;

		float Distance = FVector2D::Dist(ActorLocation, Monster->GetActorLocation());

		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestMonster = Monster;
		}
	}

	return ClosestMonster;
}
