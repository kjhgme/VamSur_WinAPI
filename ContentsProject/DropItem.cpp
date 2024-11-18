#include "PreCompile.h"
#include "DropItem.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineAPICore.h>
#include "Player.h"

ADropItem::ADropItem()
{
}

ADropItem::~ADropItem()
{
}

void ADropItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ItemToPlayer(_DeltaTime);
}

void ADropItem::InitDropItem(FVector2D _Pos)
{
	SetActorLocation(_Pos);

	InitCollision(_Pos);

	DebugOn();
}

void ADropItem::InitCollision(FVector2D _Pos)
{
	FVector2D scale = SpriteRenderer->GetComponentScale();

	CollisionComponent = CreateDefaultSubObject<U2DCollision>();
	CollisionComponent->SetComponentLocation({0.0f, 0.0f});
	CollisionComponent->SetComponentScale(scale);
	CollisionComponent->SetCollisionGroup(ECollisionGroup::DropItemBody);
	CollisionComponent->SetCollisionType(ECollisionType::CirCle);

	CollisionComponent->SetCollisionEnter(std::bind(&ADropItem::CollisionEnter, this, std::placeholders::_1));
}

void ADropItem::CollisionEnter(AActor* _ColActor)
{
	ApplyItemEffect();
}

void ADropItem::ApplyItemEffect()
{
	IsPickedUp = true;

	CollisionComponent->SetActive(false);
	ItemPos = GetActorLocation();
	PlayerPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	FVector2D DiffPos = PlayerPos - ItemPos;

	DiffPos.X = UEngineMath::Clamp(DiffPos.X, -1.0f, 1.0f);
	DiffPos.Y = UEngineMath::Clamp(DiffPos.Y, -1.0f, 1.0f);

	KnockBack = -DiffPos;
}

void ADropItem::ItemToPlayer(float _DeltaTime)
{
	if (true == IsPickedUp)
	{
		KnockBackTime += _DeltaTime;

		if (false == IsReturning)
		{
			AddActorLocation({ KnockBack.X * 2.0f * APlayer::PlayerStatus.Speed * _DeltaTime,
							KnockBack.Y * 2.0f * APlayer::PlayerStatus.Speed * _DeltaTime });
		
			if (0.25f <= KnockBackTime)
			{
				IsReturning = true;
				KnockBackTime = 0.0f;
			}
		}
		else
		{
			ItemPos = GetActorLocation();
			PlayerPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

			FVector2D NewPos = FVector2D::Lerp(ItemPos, PlayerPos, _DeltaTime * 8.0f);
			SetActorLocation(NewPos);

			FVector2D DiffPos = PlayerPos - ItemPos;

			if (
				(UEngineMath::Abs(DiffPos.X) <= 50.0f && UEngineMath::Abs(DiffPos.Y) <= 50.0f))
			{
				Destroy();
			}
		}
	}
}
