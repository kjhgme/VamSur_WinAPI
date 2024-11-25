#pragma once
#include "Weapon.h"
#include <deque>

struct DirectionCondition {
	bool HeadDirRight;
	bool HeadDirTop;
	bool HeadDirBottom;
	bool HeadDirStationary;
	int SpriteNum;
	FVector2D KnifePos;
};

const std::vector<DirectionCondition> DirectionMapping = {
	{ true,  false, false, false, 00, {1.0f, 0.0f} },
	{ true,  false, false, true, 00, {1.0f, 0.0f} },
	{ true,  false, true, false, 01, {1.0f, 1.0f} },
	{ false, false, true, true, 02, {0.0f, 1.0f} },
	{ true, false, true, true, 02, {0.0f, 1.0f} },
	{ false, false, true, false, 03, {-1.0f, 0.0f} },
	{ false, false, false, false, 04, {-1.0f, 0.0f} },
	{ false, false, false, true, 04, {-1.0f, 0.0f} },
	{ false, true,  false, false, 05, {-1.0f, -1.0f} },
	{ false, true,  false, true, 06, {0.0f, -1.0f} },
	{ true, true,  false, true, 06, {0.0f, -1.0f} },
	{ true,  true,  false, false, 07, {1.0f, -1.0f} },
};

static const std::unordered_map<int, FVector2D> MoveOffsets = {
	{ 00, { 2.0f,  0.0f } },
	{ 01, { 2.0f,  2.0f } },
	{ 02, { 0.0f,  2.0f } },
	{ 03, { -2.0f, 2.0f } },
	{ 04, { -2.0f, 0.0f } },
	{ 05, { -2.0f, -2.0f } },
	{ 06, { 0.0f,  -2.0f } },
	{ 07, { 2.0f,  -2.0f } }
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

	void Attack();

	void PopKnife();

	void SetFireRendererProperties(USpriteRenderer* _Renderer, int _SpriteNum, FVector2D _Pos);

protected:

private:
	std::deque<std::pair<int, USpriteRenderer*>> KnifeRenderers;
	std::deque<class U2DCollision*> CollisionComponents;
	float Time = 0.0f;

	class APlayer* player = nullptr;
};

