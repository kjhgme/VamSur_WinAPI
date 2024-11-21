#include "PreCompile.h"
#include "LevelUpUI.h"
#include "ContentsEnum.h"

#include <EngineBase/EngineTimer.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include "InGameUI.h"

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
	{
		LeftCursor = CreateDefaultSubObject<USpriteRenderer>();
		LeftCursor->SetSprite("Cursor", 0);
		LeftCursor->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND)-1);
		LeftCursor->SetSpriteScale(1.0f);

		LeftCursor->CreateAnimation("Cursor_L", "Cursor", 0, 7, 0.15f);
		LeftCursor->ChangeAnimation("Cursor_L");
	}
	{
		RightCursor = CreateDefaultSubObject<USpriteRenderer>();
		RightCursor->SetSprite("Cursor", 8);
		RightCursor->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND)-1);
		RightCursor->SetSpriteScale(1.0f);

		RightCursor->CreateAnimation("Cursor_R", "Cursor", 8, 15, 0.15f);
		RightCursor->ChangeAnimation("Cursor_R");
	}
}

LevelUpUI::~LevelUpUI()
{
}

void LevelUpUI::BeginPlay()
{
	Super::BeginPlay();

	CreateWeaponUI(Weapon1Name, Weapon1StatusText, Weapon1Description, "Weapon1", "New!", "A Description.", Weapon1Y);
	CreateWeaponUI(Weapon2Name, Weapon2StatusText, Weapon2Description, "Weapon2", "LV:2", "B Description.", Weapon2Y);
	CreateWeaponUI(Weapon3Name, Weapon3StatusText, Weapon3Description, "Weapon3", "LV:3", "C Description.", Weapon3Y);
}

void LevelUpUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsActive == true)
	{
		UpdateCursorPosition();

		if (true == UEngineInput::GetInst().IsDown('K'))
		{
			SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);

			UEngineAPICore::GetCore()->GetTimer().ToggleTime();

			IsActive = false;
		}
		if (true == UEngineInput::GetInst().IsDown('W'))
		{
			pos.move("up");
		}
		else if (true == UEngineInput::GetInst().IsDown('S'))
		{
			pos.move("down");
		}
		else if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{

		}
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
	IsActive = true;
	SetOrder(static_cast<int>(ERenderOrder::UI) + 1);

	LeftCursor->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
	RightCursor->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
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

void LevelUpUI::ChangeTextBox(std::vector<std::pair<EWeaponType, WeaponLevelData>> _RandWeapons)
{
	Weapon1Name->Destroy();
	Weapon1StatusText->Destroy();
	Weapon1Description->Destroy();
	Weapon2Name->Destroy();
	Weapon2StatusText->Destroy();
	Weapon2Description->Destroy();
	Weapon3Name->Destroy();
	Weapon3StatusText->Destroy();
	Weapon3Description->Destroy();

	std::string Weapon1Type = EWeaponTypeToString(_RandWeapons[0].first);
	std::string Weapon2Type = EWeaponTypeToString(_RandWeapons[1].first);
	std::string Weapon3Type = EWeaponTypeToString(_RandWeapons[2].first);

	std::string Weapon1Level = std::to_string(_RandWeapons[0].second.Level);
	std::string Weapon2Level = std::to_string(_RandWeapons[1].second.Level);
	std::string Weapon3Level = std::to_string(_RandWeapons[2].second.Level);

	std::string Weapon1Des = _RandWeapons[0].second.Description;
	std::string Weapon2Des = _RandWeapons[1].second.Description;
	std::string Weapon3Des = _RandWeapons[2].second.Description;

	CreateWeaponUI(Weapon1Name, Weapon1StatusText, Weapon1Description, Weapon1Type, "LV:" + Weapon1Level, Weapon1Des, Weapon1Y);
	CreateWeaponUI(Weapon2Name, Weapon2StatusText, Weapon2Description, Weapon2Type, "LV:" + Weapon2Level, Weapon2Des, Weapon2Y);
	CreateWeaponUI(Weapon3Name, Weapon3StatusText, Weapon3Description, Weapon3Type, "LV:" + Weapon3Level, Weapon3Des, Weapon3Y);
}

std::string LevelUpUI::EWeaponTypeToString(EWeaponType WeaponType) {
	switch (WeaponType) {
	case EWeaponType::Whip:        return "Whip";
	case EWeaponType::MagicWand:   return "MagicWand";
	case EWeaponType::Knife:       return "Knife";
	case EWeaponType::Axe:         return "Axe";
	case EWeaponType::KingBible:   return "KingBible";
	case EWeaponType::WeaponCount: return "WeaponCount";
	default:                       return "Unknown";
	}
}

void LevelUpUI::UpdateCursorPosition()
{
	CPos currentPos = pos.GetPos();
	LeftCursor->SetComponentLocation(currentPos.LCP);
	RightCursor->SetComponentLocation(currentPos.RCP);
}
