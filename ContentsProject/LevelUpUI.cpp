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
}

void LevelUpUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsActive == true)
	{
		UpdateCursorPosition();

		if (true == UEngineInput::GetInst().IsDown('K'))
		{
			SetActive();
			UEngineAPICore::GetCore()->GetTimer().ToggleTime();

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
			if (pos.GetPosID() == LocationID::TOP)
			{
				Player->GetWeaponManager()->AddWeapon(RandomWeapons[0].first);
			}
			else if (pos.GetPosID() == LocationID::MID)
			{
				if (2 <= RandomWeapons.size())
				{
					Player->GetWeaponManager()->AddWeapon(RandomWeapons[1].first);
				}
			}
			else if (pos.GetPosID() == LocationID::BOT)
			{
				if (3 <= RandomWeapons.size())
				{
					Player->GetWeaponManager()->AddWeapon(RandomWeapons[2].first);
				}
			}

			SetActive();
			UEngineAPICore::GetCore()->GetTimer().ToggleTime();			
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
	if (IsActive == false)
	{
		IsActive = true;
		SetOrder(static_cast<int>(ERenderOrder::UI) + 1);

		LeftCursor->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
		RightCursor->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
	}
	else if (IsActive == true)
	{
		IsActive = false;
		SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);

		LeftCursor->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
		RightCursor->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
	}
}

void LevelUpUI::CreateWeaponUI(ATextBox*& NameBox, ATextBox*& StatusBox, ATextBox*& DescriptionBox,
	const std::string& Name, const std::string& Status, const std::string& Description, float PosY)
{
	NameBox = CreateTextBox(Name, { WeaponNameX, PosY });
	StatusBox = CreateTextBox(Status, { WeaponStatusX, PosY });
	DescriptionBox = CreateTextBox(Description, { WeaponDescriptionX, PosY + 50.0f });
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

	for (int i = 0; i < RandomWeapons.size(); ++i)
	{
		if (i == 0)
		{
			Weapon1Name->SetOrder(NewOrder);
			Weapon1StatusText->SetOrder(NewOrder);
			Weapon1Description->SetOrder(NewOrder);
		}
		else if (i == 1)
		{
			Weapon2Name->SetOrder(NewOrder);
			Weapon2StatusText->SetOrder(NewOrder);
			Weapon2Description->SetOrder(NewOrder);
		}
		else if (i == 2)
		{
			Weapon3Name->SetOrder(NewOrder);
			Weapon3StatusText->SetOrder(NewOrder);
			Weapon3Description->SetOrder(NewOrder);
		}
	}
}

void LevelUpUI::ChangeTextBox(std::vector<std::pair<EWeaponType, WeaponLevelData>> _RandWeapons)
{
	if (Weapon1Name) Weapon1Name->Destroy();
	if (Weapon1StatusText) Weapon1StatusText->Destroy();
	if (Weapon1Description) Weapon1Description->Destroy();
	if (Weapon2Name) Weapon2Name->Destroy();
	if (Weapon2StatusText) Weapon2StatusText->Destroy();
	if (Weapon2Description) Weapon2Description->Destroy();
	if (Weapon3Name) Weapon3Name->Destroy();
	if (Weapon3StatusText) Weapon3StatusText->Destroy();
	if (Weapon3Description) Weapon3Description->Destroy();
	RandomWeapons.clear();

	RandomWeapons = _RandWeapons;

	for (int i = 0; i < RandomWeapons.size(); ++i)
	{
		std::string WeaponType = EWeaponTypeToString(RandomWeapons[i].first);
		std::string WeaponLevel = std::to_string(RandomWeapons[i].second.Level);
		std::string WeaponDes = RandomWeapons[i].second.Description;

		if (i == 0)
		{
			CreateWeaponUI(Weapon1Name, Weapon1StatusText, Weapon1Description, WeaponType, "LV:" + WeaponLevel, WeaponDes, Weapon1Y);
		}
		else if (i == 1)
		{
			CreateWeaponUI(Weapon2Name, Weapon2StatusText, Weapon2Description, WeaponType, "LV:" + WeaponLevel, WeaponDes, Weapon2Y);
		}
		else if (i == 2)
		{
			CreateWeaponUI(Weapon3Name, Weapon3StatusText, Weapon3Description, WeaponType, "LV:" + WeaponLevel, WeaponDes, Weapon3Y);
		}
	}
}

std::string LevelUpUI::EWeaponTypeToString(EWeaponType WeaponType) {
	switch (WeaponType) {
	case EWeaponType::Whip:				return "Whip";
	case EWeaponType::MagicWand:		return "MagicWand";
	case EWeaponType::Knife:			return "Knife";
	case EWeaponType::Axe:				return "Axe";
	case EWeaponType::KingBible:		return "KingBible";
	case EWeaponType::HollowHeart:		return "HollowHeart";
	case EWeaponType::EmptyTome:		return "EmptyTome";
	case EWeaponType::Bracer:			return "Bracer";
	case EWeaponType::Candelabrador:	return "Candelabrador";
	case EWeaponType::Spellbinder:		return "Spellbinder";
	case EWeaponType::TotalCount:		return "TotalCount";
	default:							return "Unknown";
	}
}

void LevelUpUI::UpdateCursorPosition()
{
	CPos currentPos = pos.GetPos();
	LeftCursor->SetComponentLocation(currentPos.LCP);
	RightCursor->SetComponentLocation(currentPos.RCP);
}
