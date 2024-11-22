#include "PreCompile.h"
#include "TantoSkill.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include "InGameMode.h"
#include "Player.h"

ATantoSkill::ATantoSkill()
{
	{
		FireRenderers.push_back(CreateDefaultSubObject<USpriteRenderer>());		
		FireRenderers.back()->SetSprite("Fire_00.png");
		FireRenderers.back()->SetSpriteScale(1.0f);
		FireRenderers.back()->SetOrder(ERenderOrder::WEAPON);		
	}
	{
		FVector2D scale = FireRenderers.back()->GetComponentScale();
		scale.Y = scale.X;

		CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());
		CollisionComponents.back()->SetComponentLocation({ 0.0f, 0.0f });
		CollisionComponents.back()->SetComponentScale(scale);
		CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);

		//CollisionComponents.back()->SetCollisionEnter(std::bind(&ATantoSkill::CollisionEnter, this, std::placeholders::_1));
	}

	DebugOn();
}

ATantoSkill::~ATantoSkill()
{
}

void ATantoSkill::BeginPlay()
{
	Super::BeginPlay();

	player = AInGameMode::Player;

	TimeEventer.PushEvent(0.1f, std::bind(&ATantoSkill::Fire, this), false, 10.0f, false);
}

void ATantoSkill::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	for (auto& Renderer : FireRenderers)
	{
		Renderer->AddComponentLocation({ 1.0f, 0.0f });
	}

	for (auto& Collision : CollisionComponents)
	{
		Collision->AddComponentLocation({ 1.0f, 0.0f });
	}

	Time += _DeltaTime;

	if (12.0f <= Time)
		Destroy();
}

void ATantoSkill::Fire()
{
	{
		FireRenderers.push_back(CreateDefaultSubObject<USpriteRenderer>());

		for (const auto& Condition : DirectionMapping) {
			if (player->GetHeadDirRight() == Condition.HeadDirRight &&
				player->GetHeadDirTop() == Condition.HeadDirTop &&
				player->GetHeadDirBottom() == Condition.HeadDirBottom &&
				player->GetHeadDirStationary() == Condition.HeadDirStationary) {
				SetFireRendererProperties(FireRenderers.back(), Condition.SpriteName);
				break;
			}
		}
	}
	{
		FVector2D scale = FireRenderers.back()->GetComponentScale();
		scale.Y = scale.X;

		CollisionComponents.push_back(CreateDefaultSubObject<U2DCollision>());
		CollisionComponents.back()->SetComponentLocation({ 0.0f, 0.0f });
		CollisionComponents.back()->SetComponentScale(scale);
		CollisionComponents.back()->SetCollisionGroup(ECollisionGroup::WeaponBody);
		CollisionComponents.back()->SetCollisionType(ECollisionType::CirCle);
	}
}

void ATantoSkill::PopFire()
{
	PopStart = true;

	if (!FireRenderers.empty())
	{
		FireRenderers.front()->Destroy();
		FireRenderers.pop_front();
	}

	if (!CollisionComponents.empty())
	{
		CollisionComponents.front()->Destroy();
		CollisionComponents.pop_front();
	}
}

void ATantoSkill::SetFireRendererProperties(USpriteRenderer* _Renderer, const std::string& _SpriteName)
{
	_Renderer->SetSprite(_SpriteName);
	_Renderer->SetSpriteScale(1.0f);
	_Renderer->SetOrder(ERenderOrder::WEAPON);
	_Renderer->SetComponentLocation({ 0.0f, 0.0f });
}

