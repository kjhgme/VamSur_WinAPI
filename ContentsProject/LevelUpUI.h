#pragma once

#include "TextBox.h"
#include "InGameMode.h"
#include "Player.h"

class LevelUpUI : public AActor
{
public:
	LevelUpUI();
	~LevelUpUI();

	LevelUpUI(const LevelUpUI& _Other) = delete;
	LevelUpUI(LevelUpUI&& _Other) noexcept = delete;
	LevelUpUI& operator=(const LevelUpUI& _Other) = delete;
	LevelUpUI& operator=(LevelUpUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetPos();
	void SetActive();

	void CreateWeaponUI(ATextBox*& NameBox, ATextBox*& StatusBox, ATextBox*& DescriptionBox, const std::string& Name, const std::string& Status, const std::string& Description, float PosY);

	ATextBox* CreateTextBox(const std::string& Text, const FVector2D& Pos);

	void SetOrder(int NewOrder);

	void ChangeTextBox();

protected:

private:
	USpriteRenderer* LevelUpMainPanelRenderer = nullptr;
	USpriteRenderer* WeaponSelectionPanelRenderer = nullptr;

	FVector2D WindowSize{};
	FVector2D LevelUpUIPos{};
	FVector2D MainPanelScale{};

	ATextBox* Weapon1Name = nullptr;
	ATextBox* Weapon1StatusText = nullptr;
	ATextBox* Weapon1Description = nullptr;
	ATextBox* Weapon2Name = nullptr;
	ATextBox* Weapon2StatusText = nullptr;
	ATextBox* Weapon2Description = nullptr;
	ATextBox* Weapon3Name = nullptr;
	ATextBox* Weapon3StatusText = nullptr;
	ATextBox* Weapon3Description = nullptr;

	APlayer* Player = AInGameMode::Player;
};

