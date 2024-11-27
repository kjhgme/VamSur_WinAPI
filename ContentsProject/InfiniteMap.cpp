#include "PreCompile.h"
#include "InfiniteMap.h"

#include <EngineCore/EngineAPICore.h>

#include "ContentsEnum.h"

AInfiniteMap::~AInfiniteMap()
{
	InfiMap.clear();
}

void AInfiniteMap::BeginPlay()
{
    core = UEngineAPICore::GetCore();
    playerPos = core->GetCurLevel()->GetMainPawn()->GetActorLocation();

    InitMaps(StageLevel);
}

void AInfiniteMap::Tick(float _DeltaTime)
{
	playerPos = core->GetCurLevel()->GetMainPawn()->GetActorLocation();

    MapMoveCheck(playerPos);
}

void AInfiniteMap::SetStage(USpriteRenderer* _SpriteRenderer, int _level)
{
	_SpriteRenderer->SetSprite("Stage", _level);
}

void AInfiniteMap::InitMaps(int _level)
{
    InfiMap.resize(3);

    for (int i = 0; i < 3; ++i)
    {
        InfiMap[i].resize(3);
        for (int j = 0; j < 3; ++j)
        {
            USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
            SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);

            SetStage(SpriteRenderer, _level);

            MapScale = SpriteRenderer->SetSpriteScale(1.0f);

            SpriteRenderer->SetComponentLocation({ MapScale.X * (i - 1) , MapScale.Y * (j - 1) });

            InfiMap[i][j] = SpriteRenderer;
        }
    }
}

void AInfiniteMap::MapMoveCheck(FVector2D _PlayerPos)
{
    FVector2D InfiPlayerPos = _PlayerPos / MapScale;

    InfiPlayerPos = InfiPlayerPos - InfiMapPos;

    if (InfiPlayerPos.X > 0)
    {
        InfiMapPos.X += 1;

        for (int i = 0; i < 3; ++i) {
            FVector2D PrevPos = InfiMap[0][i]->GetComponentLocation();
            InfiMap[0][i]->SetComponentLocation({ PrevPos.X + (MapScale.X * 3) , PrevPos.Y});
            std::swap(InfiMap[0][i], InfiMap[1][i]);
            std::swap(InfiMap[1][i], InfiMap[2][i]);
        }
    }
    if (InfiPlayerPos.X < -2) {
        InfiMapPos.X -= 1;

        for (int i = 0; i < 3; ++i) {
            FVector2D PrevPos = InfiMap[2][i]->GetComponentLocation();
            InfiMap[2][i]->SetComponentLocation({ PrevPos.X - (MapScale.X * 3), PrevPos.Y });
            std::swap(InfiMap[0][i], InfiMap[2][i]);
            std::swap(InfiMap[1][i], InfiMap[2][i]);
        }
    }
    if (InfiPlayerPos.Y > 0) {
        InfiMapPos.Y += 1;

        for (int i = 0; i < 3; ++i) {
            FVector2D PrevPos = InfiMap[i][0]->GetComponentLocation();
            InfiMap[i][0]->SetComponentLocation({ PrevPos.X , PrevPos.Y + (MapScale.Y * 3) });
            std::swap(InfiMap[i][0], InfiMap[i][1]);
            std::swap(InfiMap[i][1], InfiMap[i][2]);
        }
    }
    if (InfiPlayerPos.Y < -2) {

        InfiMapPos.Y -= 1;

        for (int i = 0; i < 3; ++i) {
            FVector2D PrevPos = InfiMap[i][2]->GetComponentLocation();
            InfiMap[i][2]->SetComponentLocation({ PrevPos.X , PrevPos.Y - (MapScale.Y * 3) });
            std::swap(InfiMap[i][0], InfiMap[i][2]);
            std::swap(InfiMap[i][1], InfiMap[i][2]);
        }
    }
}
