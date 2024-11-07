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
    LocationID current;

    Position() : current(START) {}

    void move(const std::string& direction) {
        if (transitions[current].find(direction) != transitions[current].end()) {
            current = transitions[current][direction];
        }
    }

    CPos GetPos() {
        switch (current) {
        case BACK: 
            CursorPos = BackPos;
            break;
        case OPTION:
            CursorPos = OptionPos;
            break;
        case START:
            CursorPos = StartPos;
            break;
        case COLLECTION:
            CursorPos = CollectionPos;
            break;
        case UPGRADE:
            CursorPos = UpgradePos;
            break;
        case UNLOCK:
            CursorPos = UnlockPos;
            break;
        case MAKER:
            CursorPos = MakerPos;
            break;
        default:
            break;
        }

        return CursorPos;
    }

private:
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

    CPos CursorPos = { { -130,120 }, { 130, 120 } };
    CPos StartPos = { { -130,120 }, { 130, 120 } };
    CPos UpgradePos = { { -110,260 }, { 110, 260 } };
    CPos CollectionPos = { { -300,260 }, { -120, 260 } };
    CPos UnlockPos = { { 120,260 }, { 305, 260 } };
    CPos MakerPos = { { -90,360 }, { 90, 360 } };
    CPos BackPos = { { -258,-365 }, { -115, -365 } };
    CPos OptionPos = { { 165,-365 }, { 310, -365 } };
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
	USpriteRenderer* LeftCursor = nullptr;
	USpriteRenderer* RightCursor = nullptr;
    
    Position pos;
};