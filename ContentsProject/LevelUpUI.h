#pragma once
#include <unordered_map>

#include "TextBox.h"
#include "InGameMode.h"
#include "Player.h"
#include "WeaponManager.h"

struct CPos {
	FVector2D LCP;
	FVector2D RCP;
};

enum LocationID {
	TOP = 1,
	MID,
	BOT,
};

class LevelUPCursorPosition {
public:

	LevelUPCursorPosition() : current(TOP) {}

    void move(const std::string& direction) {
        if (transitions[current].find(direction) != transitions[current].end()) {
            current = transitions[current][direction];
        }
    }

    CPos GetPos() const {
        switch (current) {
        case TOP:
            return TOPPos;
        case MID:
            return MIDPos;
        case BOT:
            return BOTPos;
        default:
            return TOPPos;
        }
    }

    LocationID GetPosID() {
        return current;
    }

private:
    LocationID current;

    // 각 위치와 이동 가능한 방향을 정의한 해시맵
    std::unordered_map<LocationID, std::unordered_map<std::string, LocationID>> transitions = {
		{TOP, { {"down", MID} }},
        {MID, { {"up", TOP}, {"down", BOT} }},
		{BOT, { {"up", MID} }}
    };

    inline static const CPos TOPPos = { { -245.0f,-120.0f }, { 245.0f, -120.0f } };
    inline static const CPos MIDPos = { { -245.0f, 0.0f }, { 245.0f, 0.0f } };
    inline static const CPos BOTPos = { { -245.0f,120.0f }, { 245.0f, 120.0f } };
};

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

	void ChangeTextBox(std::vector<std::pair<EWeaponType, WeaponLevelData>> _RandWeapons);

	std::string EWeaponTypeToString(EWeaponType WeaponType);
		
	void UpdateCursorPosition();

	int GetWeaponIconIndex(EWeaponType WeaponType);

protected:

private:
	bool IsActive = false;

	USpriteRenderer* LevelUpMainPanelRenderer = nullptr;
	USpriteRenderer* WeaponSelectionPanelRenderer = nullptr;
	USpriteRenderer* WeaponPanelIconRenderer[3]{};

	USpriteRenderer* LeftCursor = nullptr;
	USpriteRenderer* RightCursor = nullptr;
	LevelUPCursorPosition pos;

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

	std::vector<std::pair<EWeaponType, WeaponLevelData>> RandomWeapons;
};

