#include "PreCompile.h"
#include "Knife.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

Knife::Knife()
{
	WeaponType = EWeaponType::Knife;

	LevelDescriptions = {
		{1, "Fires quickly in the faced\ndirection."},
		{2, "Fires 1 more projectile."},
		{3, "Fires 1 more projectile.\nBase Damage up by 5."},
		{4, "Fires 1 more projectile."},
		{5, "Passes through 1 more enemy."},
		{6, "Fires 1 more projectile."},
		{7, "Fires 1 more projectile.\nBase Damage up by 5."},
		{8, "Passes through 1 more enemy."},
	};
}

Knife::~Knife()
{
}

void Knife::BeginPlay()
{
	AWeapon::BeginPlay();

	player = AInGameMode::Player;

	Level = 1;
	AttackPower = 10;
	KnockBack = 1;
}

void Knife::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (size_t i = 0; i < CollisionComponents.size(); ++i)
	{
		auto& Renderer = KnifeRenderers[i];
		auto OffsetIt = KnifeMoveOffsets.find(Renderer.first);

		if (OffsetIt != KnifeMoveOffsets.end()) {
			Renderer.second->AddComponentLocation(OffsetIt->second);
		}

		const FVector2D Location = Renderer.second->GetComponentLocation();
		if (Location.X <= -1000.0f || Location.X >= 1000.0f || Location.Y <= -1000.0f || Location.Y >= 1000.0f) {
			PopKnife();
			continue;
		}

		if (i < CollisionComponents.size()) {
			CollisionComponents[i]->SetComponentLocation(Location);
		}
	}
}

void Knife::InitCollision()
{
	AWeapon::InitCollision();
}

void Knife::Action()
{
	TimeEventer.PushEvent(1.0f, std::bind(&Knife::Attack, this), false, -1.0f, true);
}

void Knife::Attack()
{
	KnifeRenderers.push_back(std::make_pair(00, CreateDefaultSubObject<USpriteRenderer>()));
	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());

	{
		for (const auto& Condition : KnifeDirMapping)
		{
			if (player->GetHeadDirRight() == Condition.HeadDirRight &&
				player->GetHeadDirTop() == Condition.HeadDirTop &&
				player->GetHeadDirBottom() == Condition.HeadDirBottom &&
				player->GetHeadDirStationary() == Condition.HeadDirStationary)
			{
				KnifeRenderers.back().first = Condition.SpriteNum;
				SetFireRendererProperties(KnifeRenderers.back().second, Condition.SpriteNum, Condition.KnifePos);

				CollisionComponents.back()->SetComponentLocation(Condition.KnifePos * player->GetPlayerScale());

				break;
			}
		}
	}
	{
		FVector2D scale = KnifeRenderers.back().second->GetComponentScale();
		scale.Y = scale.X;
		CollisionComponents.back()->SetComponentScale(scale);
		CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);
		CollisionComponents.back()->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
	}

	SetActorLocation(player->GetActorLocation());
}

void Knife::PopKnife()
{
	if (!KnifeRenderers.empty())
	{
		KnifeRenderers.front().second->Destroy();
		KnifeRenderers.pop_front();
	}

	if (!CollisionComponents.empty())
	{
		CollisionComponents.front()->Destroy();
		CollisionComponents.pop_front();
	}
}

void Knife::SetFireRendererProperties(USpriteRenderer* _Renderer, int _SpriteNum, FVector2D _Pos)
{
	_Renderer->SetSprite("Knife", _SpriteNum);
	_Renderer->SetSpriteScale(1.0f);
	_Renderer->SetOrder(ERenderOrder::WEAPON);
	_Renderer->SetComponentLocation(_Pos * player->GetPlayerScale());
}
