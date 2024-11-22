#include "PreCompile.h"
#include "KillAndGoldUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

KillAndGoldUI::KillAndGoldUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetPos();

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("InGameUI_KillAndGold.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}

    for (size_t i = 0; i < 10; i++)
    {
        USpriteRenderer* KillSprite = CreateDefaultSubObject<USpriteRenderer>();
        USpriteRenderer* GoldSprite = CreateDefaultSubObject<USpriteRenderer>();
        KillRenders.push_back(KillSprite);
		GoldRenders.push_back(GoldSprite);
    }

    SetTextSpriteName("Letters");
    SetOrder(ERenderOrder::UI);
    SetTextScale({ 14, 26 });
    SetDisplay();
}

KillAndGoldUI::~KillAndGoldUI()
{
}

void KillAndGoldUI::BeginPlay()
{
}

void KillAndGoldUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetPos();
}

void KillAndGoldUI::SetTextSpriteName(const std::string _Text)
{
    TextSpriteName = _Text;

    for (int i = 0; i < KillRenders.size(); i++)
    {
		KillRenders[i]->SetSprite(TextSpriteName, i);
		GoldRenders[i]->SetSprite(TextSpriteName, i);
    }
}

void KillAndGoldUI::SetOrder(int _Order)
{
    for (int i = 0; i < KillRenders.size(); i++)
    {
		KillRenders[i]->SetOrder(_Order);
		GoldRenders[i]->SetOrder(_Order);
    }
}

void KillAndGoldUI::SetDisplay()
{
    DisplayKillCount();
    DisplayGoldCount();
}

void KillAndGoldUI::SetPos()
{
	Pos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	SetActorLocation({ Pos });
}

void KillAndGoldUI::DisplayKillCount()
{
    std::string Number = std::to_string(KillCount);

    if (KillRenders.size() <= Number.size())
    {
        MSGASSERT("Number is Overflow.");
        return;
    }

    FVector2D LocalPos;
    LocalPos.X = 425.0f;
    LocalPos.Y = -362.0f;

    float TotalWidth = TextScale.X * Number.size();
    LocalPos.X -= TotalWidth;

    for (size_t i = 0; i < Number.size(); i++)
    {
        char Value = Number[i] - '0';
        KillRenders[i]->SetSprite(TextSpriteName, Value);
        KillRenders[i]->SetComponentScale(TextScale);
        KillRenders[i]->SetComponentLocation(LocalPos);
        LocalPos.X += TextScale.X;
        KillRenders[i]->SetActive(true);
    }

    for (size_t i = Number.size(); i < KillRenders.size(); i++)
    {
        KillRenders[i]->SetActive(false);
    }
}

void KillAndGoldUI::DisplayGoldCount()
{
    std::string Number = std::to_string(GoldCount);

    if (GoldRenders.size() <= Number.size())
    {
        MSGASSERT("Number is Overflow.");
        return;
    }

    FVector2D LocalPos;
    LocalPos.X = 610.0f;
    LocalPos.Y = -362.0f;

    float TotalWidth = TextScale.X * Number.size();
    LocalPos.X -= TotalWidth;

    for (size_t i = 0; i < Number.size(); i++)
    {
        char Value = Number[i] - '0';
        GoldRenders[i]->SetSprite(TextSpriteName, Value);
        GoldRenders[i]->SetComponentScale(TextScale);
        GoldRenders[i]->SetComponentLocation(LocalPos);
        LocalPos.X += TextScale.X;
        GoldRenders[i]->SetActive(true);
    }

    for (size_t i = Number.size(); i < GoldRenders.size(); i++)
    {
        GoldRenders[i]->SetActive(false);
    }
}

void KillAndGoldUI::AddKillCount()
{   
    KillCount++;
    DisplayKillCount();
}

void KillAndGoldUI::AddGoldCount(int _Gold)
{
    GoldCount += _Gold;
    DisplayGoldCount();
}
