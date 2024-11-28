#include "PreCompile.h"
#include "TitleUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

#include "TitleCursor.h"

ATitleUI::ATitleUI()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.Half() });

	// TopPanel
	{
		TopPanel = CreateDefaultSubObject<USpriteRenderer>();
		TopPanel->SetSprite("TitleUI_TopPanel.png");
		TopPanel->SetOrder(static_cast<int>(ERenderOrder::UI));
		TopPanel->SetSpriteScale(1.0f);
	}
	// BackButton
	{
		BackButton = CreateDefaultSubObject<USpriteRenderer>();
		BackButton->SetSprite("TitleUI_BackButton.png");
		BackButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		BackButton->SetSpriteScale(1.0f);
	}
	// MoneyPanel
	{
		MoneyPanel = CreateDefaultSubObject<USpriteRenderer>();
		MoneyPanel->SetSprite("TitleUI_MoneyPanel.png");
		MoneyPanel->SetOrder(static_cast<int>(ERenderOrder::UI));
		MoneyPanel->SetSpriteScale(1.0f);
	}
	// OptionButton
	{
		OptionButton = CreateDefaultSubObject<USpriteRenderer>();
		OptionButton->SetSprite("TitleUI_OptionButton.png");
		OptionButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		OptionButton->SetSpriteScale(1.0f);
	}
	// StartButton
	{
		StartButton = CreateDefaultSubObject<USpriteRenderer>();
		StartButton->SetSprite("TitleUI_StartButton.png");
		StartButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		StartButton->SetSpriteScale(1.0f);
	}
	// CollectionButton
	{
		CollectionButton = CreateDefaultSubObject<USpriteRenderer>();
		CollectionButton->SetSprite("TitleUI_CollectionButton.png");
		CollectionButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		CollectionButton->SetSpriteScale(1.0f);
	}
	// UpgradeButton
	{
		UpgradeButton = CreateDefaultSubObject<USpriteRenderer>();
		UpgradeButton->SetSprite("TitleUI_UpgradeButton.png");
		UpgradeButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		UpgradeButton->SetSpriteScale(1.0f);
	}
	// UnlockButton
	{
		UnlockButton = CreateDefaultSubObject<USpriteRenderer>();
		UnlockButton->SetSprite("TitleUI_UnlockButton.png");
		UnlockButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		UnlockButton->SetSpriteScale(1.0f);
	}
	// MakerButton
	{
		MakerButton = CreateDefaultSubObject<USpriteRenderer>();
		MakerButton->SetSprite("TitleUI_MakerButton.png");
		MakerButton->SetOrder(static_cast<int>(ERenderOrder::UI));
		MakerButton->SetSpriteScale(1.0f);
	}

	TopPanel->SetAlphafloat(0.0f);
	BackButton->SetAlphafloat(0.0f);
	MoneyPanel->SetAlphafloat(0.0f);
	OptionButton->SetAlphafloat(0.0f);
	StartButton->SetAlphafloat(0.0f);
	CollectionButton->SetAlphafloat(0.0f);
	UpgradeButton->SetAlphafloat(0.0f);
	UnlockButton->SetAlphafloat(0.0f);
	MakerButton->SetAlphafloat(0.0f);

	TimeEventer.PushEvent(3.0f, std::bind(&ATitleUI::Opening, this), false, -1.0f, false);
}

ATitleUI::~ATitleUI()
{
}

void ATitleUI::BeginPlay()
{
	// CursorArrow
	Cursor = GetWorld()->SpawnActor<ATitleCursor>();	
}

void ATitleUI::Opening()
{
	TopPanel->SetAlphafloat(0.7f);
	BackButton->SetAlphafloat(1.0f);
	MoneyPanel->SetAlphafloat(1.0f);
	OptionButton->SetAlphafloat(1.0f);
	StartButton->SetAlphafloat(1.0f);
	CollectionButton->SetAlphafloat(1.0f);
	UpgradeButton->SetAlphafloat(1.0f);
	UnlockButton->SetAlphafloat(1.0f);
	MakerButton->SetAlphafloat(1.0f);

	Cursor->GetLeftCursor()->SetAlphafloat(1.0f);
	Cursor->GetRightCursor()->SetAlphafloat(1.0f);
}
