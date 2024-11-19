#include "PreCompile.h"
#include "TextBox.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

ATextBox::ATextBox()
{    
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

void ATextBox::SetTextSpriteName(const std::string _Text)
{
    TextSpriteName = _Text;

    for (int i = 0; i < TextRenders.size(); i++)
    {
        TextRenders[i]->SetSprite(TextSpriteName, i);
    }
}

void ATextBox::SetOrder(int _Order)
{
    for (int i = 0; i < TextRenders.size(); i++)
    {
        TextRenders[i]->SetOrder(_Order);
    }
}

void ATextBox::SetPos(FVector2D _Pos)
{
    Pos = _Pos;

    SetActorLocation({ Pos });
}

void ATextBox::SetText(std::string_view _Text)
{
    SetSize(_Text.size());
    SetTextSpriteName("Letters");
    SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
    SetTextScale({ 18, 42 });
    SetPos();

	FVector2D Pos = FVector2D::ZERO;

	for (size_t i = 0; i < _Text.size(); i++)
	{
		char Value = _Text[i];

        if (Value == ' ')
        {
            Pos.X += TextScale.X;
            continue;
        }
        if (Value == '\n')
        {
            Pos.X = 0.0f;
            Pos.Y += TextScale.Y;
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
        TextRenders[i]->SetComponentLocation(Pos);
		Pos.X += TextScale.X;
        TextRenders[i]->SetActive(true);
	}

	for (size_t i = _Text.size(); i < TextRenders.size(); i++)
	{
        TextRenders[i]->SetActive(false);
	}
}

void ATextBox::SetSize(int _Size)
{
    TextRenders.clear();

    for (size_t i = 0; i < _Size; i++)
    {
        USpriteRenderer* Sprite = CreateDefaultSubObject<USpriteRenderer>();
        TextRenders.push_back(Sprite);
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
    case '.': return 63;
    case ',': return 64;
    case '(': return 65;
    case ')': return 66;
    case '!': return 67;
    default: return -1; 
    }
}
