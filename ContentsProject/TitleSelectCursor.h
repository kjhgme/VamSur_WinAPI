#pragma once
#include <unordered_map>

struct CPos {
    FVector2D LCP;
    FVector2D RCP;
};

enum LocationID {
    BACK = 1,
    OPTION,
    CHARACTER_00,
    CHARACTER_01,
};

class TitleSelectPosition {
public:

    TitleSelectPosition() : current(CHARACTER_00) {}

    void move(const std::string& direction) {
        if (transitions[current].find(direction) != transitions[current].end()) {
            current = transitions[current][direction];
        }
    }

    CPos GetPos() const {
        switch (current) {
        case BACK:
            return BackPos;
        case OPTION:
            return OptionPos;
        case CHARACTER_00:
            return Charater00Pos;
        case CHARACTER_01:
            return Charater01Pos;
        default:
            return Charater00Pos;
        }
    }

    LocationID GetPosID() {
        return current;
    }

private:
    LocationID current;

    // 각 위치와 이동 가능한 방향을 정의한 해시맵
    std::unordered_map<LocationID, std::unordered_map<std::string, LocationID>> transitions = {
        {BACK, {{"right", OPTION}, {"down", CHARACTER_00}}},
        {OPTION, {{"left", BACK}, {"down", CHARACTER_01}}},
        {CHARACTER_00, {{"right", CHARACTER_01}, {"up", BACK}}},
        {CHARACTER_01, {{"left", CHARACTER_00}, {"up", BACK}}},
    };

    inline static const CPos BackPos = { { -258, -365 }, { -115, -365 } };
    inline static const CPos OptionPos = { { 165, -365 }, { 310, -365 } };

    inline static const CPos Charater00Pos = { { -305, -180 }, { -140, -180 } };
    inline static const CPos Charater01Pos = { { -160, -180  }, { 5, -180  } };
};

class ATitleSelectCursor : public AActor
{
public:
	ATitleSelectCursor();
	~ATitleSelectCursor();

	ATitleSelectCursor(const ATitleSelectCursor& _Other) = delete;
	ATitleSelectCursor(ATitleSelectCursor&& _Other) noexcept = delete;
	ATitleSelectCursor& operator=(const ATitleSelectCursor& _Other) = delete;
	ATitleSelectCursor& operator=(ATitleSelectCursor&& _Other) noexcept = delete;
   
    void BeginPlay() override;
    void Tick(float _DeltaTime) override;

    bool Alive = true;

protected:

private:
    void UpdateCursorPosition();

    USpriteRenderer* LeftCursor = nullptr;
    USpriteRenderer* RightCursor = nullptr;

    TitleSelectPosition pos;
};

