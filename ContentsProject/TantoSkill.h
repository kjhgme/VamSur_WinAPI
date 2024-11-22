#pragma once
#include <deque>

struct DirectionCondition {
	bool HeadDirRight;
	bool HeadDirTop;
	bool HeadDirBottom;
	bool HeadDirStationary;
	std::string SpriteName;
	FVector2D FirePos;
};

const std::vector<DirectionCondition> DirectionMapping = {
	{ true,  false, false, false, "Fire_RC.png", {1.0f, 0.0f} },
	{ true,  false, false, true, "Fire_RC.png", {1.0f, 0.0f} },
	{ true,  false, true, false, "Fire_RD.png", {1.0f, 1.0f} },
	{ false, false, true, true, "Fire_CD.png", {0.0f, 1.0f} },
	{ true, false, true, true, "Fire_CD.png", {0.0f, 1.0f} },
	{ false, false, true, false, "Fire_LD.png", {-1.0f, 0.0f} },
	{ false, false, false, false, "Fire_LC.png", {-1.0f, 0.0f} },
	{ false, false, false, true, "Fire_LC.png", {-1.0f, 0.0f} },
	{ false, true,  false, false, "Fire_LU.png", {-1.0f, -1.0f} },
	{ false, true,  false, true, "Fire_CU.png", {0.0f, -1.0f} },
	{ true, true,  false, true, "Fire_CU.png", {0.0f, -1.0f} },
	{ true,  true,  false, false, "Fire_RU.png", {1.0f, -1.0f} },
};

class ATantoSkill : public AActor
{
public:
	ATantoSkill();
	~ATantoSkill();

	ATantoSkill(const ATantoSkill& _Other) = delete;
	ATantoSkill(ATantoSkill&& _Other) noexcept = delete;
	ATantoSkill& operator=(const ATantoSkill& _Other) = delete;
	ATantoSkill& operator=(ATantoSkill&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Fire();
	void PopFire();

	void SetFireRendererProperties(USpriteRenderer* _Renderer, const std::string& _SpriteName, FVector2D _Pos);

protected:

private:
	std::deque<std::pair<std::string, USpriteRenderer*>> FireRenderers;
	std::deque<class U2DCollision*> CollisionComponents;
	float Time = 0.0f;

	class APlayer* player = nullptr;
};

