#pragma once
#include <deque>
#include "Weapon.h"

struct FireDirCondition {
	bool HeadDirRight;
	bool HeadDirTop;
	bool HeadDirBottom;
	bool HeadDirStationary;
	std::string SpriteName;
	FVector2D FirePos;
};

const std::vector<FireDirCondition> FireDirMapping = {
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

static const std::unordered_map<std::string, FVector2D> TtMoveOffsets = {
	{ "Fire_RC.png", { 2.0f,  0.0f } },
	{ "Fire_RD.png", { 2.0f,  2.0f } },
	{ "Fire_CD.png", { 0.0f,  2.0f } },
	{ "Fire_LD.png", { -2.0f, 2.0f } },
	{ "Fire_LC.png", { -2.0f, 0.0f } },
	{ "Fire_LU.png", { -2.0f, -2.0f } },
	{ "Fire_CU.png", { 0.0f,  -2.0f } },
	{ "Fire_RU.png", { 2.0f,  -2.0f } }
};

class TantoSkill : public AWeapon
{
public:
	TantoSkill();
	~TantoSkill();

	TantoSkill(const TantoSkill& _Other) = delete;
	TantoSkill(TantoSkill&& _Other) noexcept = delete;
	TantoSkill& operator=(const TantoSkill& _Other) = delete;
	TantoSkill& operator=(TantoSkill&& _Other) noexcept = delete;

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

