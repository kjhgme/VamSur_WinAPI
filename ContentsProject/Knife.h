#pragma once
#include "Weapon.h"
#include <deque>

struct KnifeDirCondition {
	bool HeadDirRight;
	bool HeadDirTop;
	bool HeadDirBottom;
	bool HeadDirStationary;
	int SpriteNum;
	FVector2D KnifePos;
};

const std::vector<KnifeDirCondition> KnifeDirMapping {
	{ true,  false, false, false, 0, {1.0f, 0.0f} },
	{ true,  false, false, true, 0, {1.0f, 0.0f} },
	{ true,  false, true, false, 1, {1.0f, 1.0f} },
	{ false, false, true, true, 2, {0.0f, 1.0f} },
	{ true, false, true, true, 2, {0.0f, 1.0f} },
	{ false, false, true, false, 3, {-1.0f, 0.0f} },
	{ false, false, false, false, 4, {-1.0f, 0.0f} },
	{ false, false, false, true, 4, {-1.0f, 0.0f} },
	{ false, true,  false, false, 5, {-1.0f, -1.0f} },
	{ false, true,  false, true, 6, {0.0f, -1.0f} },
	{ true, true,  false, true, 6, {0.0f, -1.0f} },
	{ true,  true,  false, false, 7, {1.0f, -1.0f} },
};

static const std::unordered_map<int, FVector2D> KnifeMoveOffsets = {
	{ 00, { 3.0f,  0.0f } },
	{ 01, { 3.0f,  3.0f } },
	{ 02, { 0.0f,  3.0f } },
	{ 03, { -3.0f, 3.0f } },
	{ 04, { -3.0f, 0.0f } },
	{ 05, { -3.0f, -3.0f } },
	{ 06, { 0.0f,  -3.0f } },
	{ 07, { 3.0f,  -3.0f } }
};

class Knife : public AWeapon
{
public:
	Knife();
	~Knife();

	Knife(const Knife& _Other) = delete;
	Knife(Knife&& _Other) noexcept = delete;
	Knife& operator=(const Knife& _Other) = delete;
	Knife& operator=(Knife&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision() override;
	void Action() override;
	void LevelUp() override;

	void Attack();

	void PopKnife();

	void SetFireRendererProperties(USpriteRenderer* _Renderer, int _SpriteNum, FVector2D _Pos);

protected:

private:
	std::deque<std::pair<int, USpriteRenderer*>> KnifeRenderers;
	std::deque<class U2DCollision*> CollisionComponents;

	class APlayer* player = nullptr;

	int EnterCount = 0;
};

