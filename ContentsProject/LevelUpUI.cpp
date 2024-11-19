#include "PreCompile.h"
#include "LevelUpUI.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include "InGameUI.h"
#include "Player.h"

constexpr float WeaponNameX = 500.0f;
constexpr float WeaponStatusX = 700.0f;
constexpr float WeaponDescriptionX = 450.0f;

constexpr float Weapon1Y = 250.0f;
constexpr float Weapon2Y = 370.0f;
constexpr float Weapon3Y = 485.0f;

LevelUpUI::LevelUpUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetPos();

	{
		LevelUpMainPanelRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LevelUpMainPanelRenderer->SetSprite("InGameUI_LevelUpPanel.png");
		LevelUpMainPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
		LevelUpMainPanelRenderer->SetSpriteScale(1.0f);

		MainPanelScale = LevelUpMainPanelRenderer->GetComponentScale();
	}

	{
		WeaponSelectionPanelRenderer = CreateDefaultSubObject<USpriteRenderer>();
		WeaponSelectionPanelRenderer->SetSprite("InGameUI_LevelUpWeapons.png");
		WeaponSelectionPanelRenderer->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
		WeaponSelectionPanelRenderer->SetSpriteScale(1.0f);
	}	
}

LevelUpUI::~LevelUpUI()
{
}

void LevelUpUI::BeginPlay()
{
	Super::BeginPlay();

	CreateWeaponUI(Weapon1Name, Weapon1StatusText, Weapon1Description, "Whip", "New!", "A Description.", Weapon1Y);
	CreateWeaponUI(Weapon2Name, Weapon2StatusText, Weapon2Description, "Weapon2", "LV:2", "B Description.", Weapon2Y);
	CreateWeaponUI(Weapon3Name, Weapon3StatusText, Weapon3Description, "Weapon3", "LV:3", "C Description.", Weapon3Y);
}

void LevelUpUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('K'))
	{
		SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);

		UEngineAPICore::GetCore()->GetTimer().ToggleTime();
	}

	SetPos();
}

void LevelUpUI::SetPos()
{
	LevelUpUIPos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();
	LevelUpUIPos.Y = LevelUpUIPos.Y - WindowSize.Half().Y + MainPanelScale.Half().Y;

	SetActorLocation({ LevelUpUIPos });
}

void LevelUpUI::SetActive()
{
	SetOrder(static_cast<int>(ERenderOrder::UI) + 1);
}

void LevelUpUI::CreateWeaponUI(ATextBox*& NameBox, ATextBox*& StatusBox, ATextBox*& DescriptionBox,
	const std::string& Name, const std::string& Status, const std::string& Description, float PosY)
{
	NameBox = CreateTextBox(Name, { WeaponNameX, PosY });
	StatusBox = CreateTextBox(Status, { WeaponStatusX, PosY });
	DescriptionBox = CreateTextBox(Description, { WeaponDescriptionX, PosY + 60.0f });
}

ATextBox* LevelUpUI::CreateTextBox(const std::string& Text, const FVector2D& Pos)
{
	ATextBox* TextBox = GetWorld()->SpawnActor<ATextBox>();
	TextBox->InitOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
	TextBox->SetTextScale(12);
	TextBox->SetText(Text);
	TextBox->SetPos(Pos);
	return TextBox;
}

void LevelUpUI::SetOrder(int NewOrder)
{
	LevelUpMainPanelRenderer->SetOrder(NewOrder);
	WeaponSelectionPanelRenderer->SetOrder(NewOrder);

	Weapon1Name->SetOrder(NewOrder);
	Weapon1StatusText->SetOrder(NewOrder);
	Weapon1Description->SetOrder(NewOrder);

	Weapon2Name->SetOrder(NewOrder);
	Weapon2StatusText->SetOrder(NewOrder);
	Weapon2Description->SetOrder(NewOrder);

	Weapon3Name->SetOrder(NewOrder);
	Weapon3StatusText->SetOrder(NewOrder);
	Weapon3Description->SetOrder(NewOrder);
}