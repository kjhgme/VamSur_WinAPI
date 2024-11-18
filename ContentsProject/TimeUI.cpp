#include "Precompile.h"
#include "TimeUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

ATimeUI::ATimeUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	for (size_t i = 0; i < 10; i++)
	{
		USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
		KillRenders.push_back(Sprite);
	}

	SetTextSpriteName("Letters");
	SetOrder(ERenderOrder::UI);
	SetTextScale({ 18, 42 });
	SetDisplayTime(0);
}

ATimeUI::~ATimeUI()
{
}

void ATimeUI::BeginPlay()
{
}

void ATimeUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	SetPos();
	SetDisplayTime(_DeltaTime);
}

void ATimeUI::SetTextSpriteName(const std::string _Text)
{
	TextSpriteName = _Text;

	for (int i = 0; i < KillRenders.size(); i++)
	{
		KillRenders[i]->SetSprite(TextSpriteName, i);
	}
}

void ATimeUI::SetOrder(int _Order)
{
	for (int i = 0; i < KillRenders.size(); i++)
	{
		KillRenders[i]->SetOrder(_Order);
	}
}

void ATimeUI::SetDisplayTime(float _DeltaTime)
{
	Time += _DeltaTime;

    Minutes = static_cast<int>(Time) / 60;
    Seconds = static_cast<int>(Time) % 60;

    std::string MinuteString = (Minutes < 10 ? "0" : "") + std::to_string(Minutes);
    std::string SecondString = (Seconds < 10 ? "0" : "") + std::to_string(Seconds);

    std::string CombinedTime = MinuteString + ":" + SecondString;

    if (KillRenders.size() < CombinedTime.size())
    {
        MSGASSERT("TimeUI is overflow.");
        return;
    }

    FVector2D Pos = FVector2D::ZERO;

    for (int i = 0; i < CombinedTime.size(); i++)
    {
        char Value = CombinedTime[i];

        if (Value >= '0' && Value <= '9')
        {
            KillRenders[i]->SetSprite(TextSpriteName, Value - '0');
        }
        else
        {
            KillRenders[i]->SetSprite(TextSpriteName, 10);
        }

        KillRenders[i]->SetComponentScale(TextScale);
        KillRenders[i]->SetComponentLocation(Pos);
        Pos.X += TextScale.X;
        KillRenders[i]->SetActive(true);
    }

    for (size_t i = CombinedTime.size(); i < KillRenders.size(); i++)
    {
        KillRenders[i]->SetActive(false);
    }
}

void ATimeUI::SetPos()
{
    Pos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
    Pos.X = Pos.X - 40.0f;
    Pos.Y = Pos.Y - WindowSize.Half().Y + 50.0f;

    SetActorLocation({ Pos });
}