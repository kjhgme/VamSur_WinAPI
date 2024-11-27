#include "PreCompile.h"
#include "TextBox.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

ATextBox::ATextBox()
{
    SetSize(0);
    SetTextSpriteName();
    SetText("");
}

ATextBox::~ATextBox()
{
}

void ATextBox::BeginPlay()
{
    Super::BeginPlay();    
}

void ATextBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATextBox::SetTextSpriteName(const std::string& _Text)
{
    TextSpriteName = _Text;

    for (int i = 0; i < TextRenders.size(); i++)
    {
        TextRenders[i]->SetSprite(TextSpriteName, i);
    }
}

void ATextBox::SetOrder()
{
    for (int i = 0; i < TextRenders.size(); i++)
    {
        TextRenders[i]->SetOrder(Order);
    }
}

void ATextBox::SetPos(FVector2D _Pos)
{
    TextPos = _Pos;

    SetActorLocation({ TextPos });
}

void ATextBox::SetText(const std::string& _Text, const std::string& _Font)
{
    SetSize(static_cast<int>(_Text.size()));
    SetTextSpriteName(_Font);
    SetOrder();

    FVector2D StartPos = FVector2D::ZERO;

    if (false == AlignLeft)
    {
        float TotalWidth = TextScale.X * _Text.size();
        StartPos.X -= TotalWidth;
    }

    FVector2D CurrentPos = StartPos;

	for (size_t i = 0; i < _Text.size(); i++)
	{
		char Value = _Text[i];

        if (Value == ' ')
        {
            CurrentPos.X += TextScale.X;
            continue;
        }
        if (Value == '\n')
        {
            CurrentPos.X = StartPos.X;
            CurrentPos.Y += TextScale.Y;
            continue;
        }
        int SpriteIndex = MapCharacterToSpriteIndex(Value);
        if (SpriteIndex == -1)
        {
            MSGASSERT("지원하지 않는 문자입니다.");
            continue;
        }

        TextRenders[i]->SetSprite(TextSpriteName, SpriteIndex);
        TextRenders[i]->SetComponentScale(TextScale);
        TextRenders[i]->SetComponentLocation(CurrentPos);
        CurrentPos.X += TextScale.X;
        TextRenders[i]->SetActive(true);        
	}

	for (size_t i = _Text.size(); i < TextRenders.size(); i++)
	{
        TextRenders[i]->SetActive(false);
	}
}

void ATextBox::SetSize(int _Size)
{
    if (_Size > TextRenders.size())
    {
        for (size_t i = TextRenders.size(); i < _Size; i++)
        {
            USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
            Sprite->SetCameraEffect(false);
            TextRenders.push_back(Sprite);
        }
    }
}

int ATextBox::MapCharacterToSpriteIndex(char Character)
{
    if (Character >= '0' && Character <= '9')
    {
        return Character - '0';
    }
    if (Character >= 'A' && Character <= 'Z')
    {
        return Character - 'A' + 11;
    }
    if (Character >= 'a' && Character <= 'z')
    {
        return Character - 'a' + 37;
    }

    //기호 매핑
    switch (Character)
    {
    case ':': return 10;
    case '.': return 63;
    case ',': return 64;
    case '(': return 65;
    case ')': return 66;
    case '!': return 67;
    case '%': return 68;
    default: return -1; 
    }
}
