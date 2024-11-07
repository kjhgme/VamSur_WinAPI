#pragma once
#include <unordered_map>

struct CPos {
	FVector2D LCP;
	FVector2D RCP;
};

enum LocationID {
    BACK = 1,
    OPTION,
    START,
    COLLECTION,
    UPGRADE,
    UNLOCK,
    MAKER
};

class Position {
public:

    Position() : current(START) {}

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
        case START:
            return StartPos;
        case COLLECTION:
            return CollectionPos;
        case UPGRADE:
            return UpgradePos;
        case UNLOCK:
            return UnlockPos;
        case MAKER:
            return MakerPos;
        default:
            return StartPos;
        }
    }

private:
    LocationID current;

    // 각 위치와 이동 가능한 방향을 정의한 해시맵
    std::unordered_map<LocationID, std::unordered_map<std::string, LocationID>> transitions = {
        {START, {{"up", BACK}, {"down", UPGRADE}}},
        {BACK, {{"right", OPTION}, {"down", START}}},
        {OPTION, {{"left", BACK}, {"down", START}}},
        {COLLECTION, {{"up", START}, {"right", UPGRADE}, {"down", MAKER}}},
        {UPGRADE, {{"up", START}, {"right", UNLOCK}, {"left", COLLECTION}, {"down", MAKER}}},
        {UNLOCK, {{"up", START}, {"left", UPGRADE}, {"down", MAKER}}},
        {MAKER, {{"up", UPGRADE}}}
    };

    inline static const CPos CursorPos = { { -130,120 }, { 130, 120 } };
    inline static const CPos StartPos = { { -130,120 }, { 130, 120 } };
    inline static const CPos UpgradePos = { { -110,260 }, { 110, 260 } };
    inline static const CPos CollectionPos = { { -300,260 }, { -120, 260 } };
    inline static const CPos UnlockPos = { { 120,260 }, { 305, 260 } };
    inline static const CPos MakerPos = { { -90,360 }, { 90, 360 } };
    inline static const CPos BackPos = { { -258,-365 }, { -115, -365 } };
    inline static const CPos OptionPos = { { 165,-365 }, { 310, -365 } };
};  

class ATitleCursor : public AActor
{
public:
	ATitleCursor();
	~ATitleCursor();

	ATitleCursor(const ATitleCursor& _Other) = delete;
	ATitleCursor(ATitleCursor&& _Other) noexcept = delete;
	ATitleCursor& operator=(const ATitleCursor& _Other) = delete;
	ATitleCursor& operator=(ATitleCursor&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
    void UpdateCursorPosition();

	USpriteRenderer* LeftCursor = nullptr;
	USpriteRenderer* RightCursor = nullptr;
    
    Position pos;
};