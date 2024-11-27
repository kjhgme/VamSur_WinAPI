#include "PreCompile.h"
#include "TantoSkill.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineRandom.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/2DCollision.h>
#include "InGameMode.h"
#include "Player.h"

UEngineRandom RandomGenerator;

TantoSkill::TantoSkill()
{
	DebugOn();
}

TantoSkill::~TantoSkill()
{
}

void TantoSkill::BeginPlay()
{
	Super::BeginPlay();

	player = AInGameMode::Player;

	AttackPower = 30;
	KnockBack = 1;

	TimeEventer.PushEvent(0.1f, std::bind(&TantoSkill::Fire, this), false, 10.0f, false);
}

void TantoSkill::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetActorLocation(player->GetActorLocation());

	for (size_t i = 0; i < FireRenderers.size(); ++i)
	{
		auto& Renderer = FireRenderers[i];
		auto OffsetIt = TtMoveOffsets.find(Renderer.first);
		
		if (OffsetIt != TtMoveOffsets.end()) {
			Renderer.second->AddComponentLocation(OffsetIt->second);

			if (0 == OffsetIt->second.X)
			{
				Renderer.second->AddComponentLocation({ RandomGenerator.Randomfloat(-5.0f, 5.0f), 0.0f});
			}
			else if (0 == OffsetIt->second.Y)
			{
				Renderer.second->AddComponentLocation({ 0.0f, RandomGenerator.Randomfloat(-5.0f, 5.0f) });
			}
			else
			{
				Renderer.second->AddComponentLocation({ RandomGenerator.Randomfloat(-5.0f, 5.0f), RandomGenerator.Randomfloat(-5.0f, 5.0f) });
			}
		}

		const FVector2D Location = Renderer.second->GetComponentLocation();
		if (Location.X <= -500.0f || Location.X >= 500.0f || Location.Y <= -500.0f || Location.Y >= 500.0f) {
			PopFire();
			continue;
		}

		if (i < CollisionComponents.size()) {
			CollisionComponents[i]->SetComponentLocation(Location);
		}
	}

	Time += _DeltaTime;

	if (12.0f <= Time)
		Destroy();
}

void TantoSkill::Fire()
{	
	FireRenderers.push_back(std::make_pair("Fire_RC.png", CreateDefaultSubObject<USpriteRenderer>()));
	CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());

	{
		for (const auto& Condition : FireDirMapping) 
		{
			if (player->GetHeadDirRight() == Condition.HeadDirRight &&
				player->GetHeadDirTop() == Condition.HeadDirTop &&
				player->GetHeadDirBottom() == Condition.HeadDirBottom &&
				player->GetHeadDirStationary() == Condition.HeadDirStationary) 
			{
				FireRenderers.back().first = Condition.SpriteName;
				SetFireRendererProperties(FireRenderers.back().second, Condition.SpriteName, Condition.FirePos);

				CollisionComponents.back()->SetComponentLocation(Condition.FirePos * player->GetPlayerScale());

				break;
			}
		}
	}
	{
		FVector2D scale = FireRenderers.back().second->GetComponentScale();
		scale.Y = scale.X;
		CollisionComponents.back()->SetComponentScale(scale);
		CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);
		CollisionComponents.back()->SetCollisionEnter(std::bind(&AWeapon::CollisionEnter, this, std::placeholders::_1));
	}
}

void TantoSkill::PopFire()
{
	if (!FireRenderers.empty())
	{
		FireRenderers.front().second->Destroy();
		FireRenderers.pop_front();
	}

	if (!CollisionComponents.empty())
	{
		CollisionComponents.front()->Destroy();
		CollisionComponents.pop_front();
	}
}

void TantoSkill::SetFireRendererProperties(USpriteRenderer* _Renderer, const std::string& _SpriteName, FVector2D _Pos)
{
	_Renderer->SetSprite(_SpriteName);
	_Renderer->SetSpriteScale(1.0f);
	_Renderer->SetOrder(ERenderOrder::WEAPON);
	_Renderer->SetComponentLocation(_Pos * player->GetPlayerScale());
}

