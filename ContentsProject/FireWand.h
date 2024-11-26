#pragma once
#include "Weapon.h"
#include <deque>

struct FireWandDirCondition {
	int RanAngle;
	std::string SpriteName;
	FVector2D Pos;
};

const std::vector<FireWandDirCondition> FireWandDirMapping = {
	{ 0, "Fire_RC.png", {1.0f, 0.0f}},
	{ 1, "Fire_RD.png", {1.0f, 1.0f} },
	{ 2, "Fire_CD.png", {0.0f, 1.0f} },
	{ 3, "Fire_LD.png", {-1.0f, 1.0f} },
	{ 4, "Fire_LC.png", {-1.0f, 0.0f} },
	{ 5, "Fire_LU.png", {-1.0f, -1.0f} },
	{ 6, "Fire_CU.png", {0.0f, -1.0f} },
	{ 7, "Fire_RU.png", {1.0f, -1.0f} }
};

static const std::unordered_map<std::string, FVector2D> FWMoveOffsets = {
	{ "Fire_RC.png", { 2.0f,  0.0f } },
	{ "Fire_RD.png", { 2.0f,  2.0f } },
	{ "Fire_CD.png", { 0.0f,  2.0f } },
	{ "Fire_LD.png", { -2.0f, 2.0f } },
	{ "Fire_LC.png", { -2.0f, 0.0f } },
	{ "Fire_LU.png", { -2.0f, -2.0f } },
	{ "Fire_CU.png", { 0.0f,  -2.0f } },
	{ "Fire_RU.png", { 2.0f,  -2.0f } }
};

class FireWand : public AWeapon
{
public:
	FireWand();
	~FireWand();

	FireWand(const FireWand& _Other) = delete;
	FireWand(FireWand&& _Other) noexcept = delete;
	FireWand& operator=(const FireWand& _Other) = delete;
	FireWand& operator=(FireWand&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision();
	void Action() override;
	void LevelUp() override;

	void Attack();
	void ShootFire();
	void PopFireWand();

	void SetFireRendererProperties(USpriteRenderer* _Renderer, const std::string& _SpriteName, FVector2D _Pos);
	
protected:

private:
	std::deque<std::pair<std::string, USpriteRenderer*>> FireWandRenderers;
	std::deque<class U2DCollision*> CollisionComponents;

	class APlayer* player = nullptr;
	FVector2D Dir{};
};

