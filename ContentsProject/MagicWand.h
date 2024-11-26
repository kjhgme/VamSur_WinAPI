#pragma once
#include "Weapon.h"
#include <deque>

struct WandDirCondition {
	float DirMinX;
	float DirMaxX;
	float DirMinY;
	float DirMaxY;
	int SpriteNum;
	FVector2D Pos;
};

const std::vector<WandDirCondition> MagicWandDirMapping{
	{  0.0f,  1.0f, -0.33f, 0.33f, 0, {1.0f, 0.0f} },
	{  0.0f,  1.0f,  0.33f, 0.66f, 1, {1.0f, 1.0f} },
	{ -1.0f,  1.0f,  0.66f, 1.0f, 2, {0.0f, 1.0f} },
	{ -1.0f,  0.0f,  0.33f, 0.66f, 3, {-1.0f, 1.0f} },
	{ -1.0f,  0.0f, -0.33f, 0.33f, 4, {-1.0f, 0.0f} },
	{ -1.0f,  0.0f, -0.66f,-0.33f, 5, {-1.0f, -1.0f} },
	{ -1.0f,  1.0f, -1.0f, -0.66f, 6, {0.0f, -1.0f} },
	{  0.0f,  1.0f, -0.66f, 0.33f, 7, {1.0f, -1.0f} } 
};

static const std::unordered_map<int, FVector2D> MagicMoveOffsets = {
	{ 00, { 3.0f,  0.0f } },
	{ 01, { 3.0f,  3.0f } },
	{ 02, { 0.0f,  3.0f } },
	{ 03, { -3.0f, 3.0f } },
	{ 04, { -3.0f, 0.0f } },
	{ 05, { -3.0f, -3.0f } },
	{ 06, { 0.0f,  -3.0f } },
	{ 07, { 3.0f,  -3.0f } }
};

class MagicWand : public AWeapon
{
public:
	MagicWand();
	~MagicWand();

	MagicWand(const MagicWand& _Other) = delete;
	MagicWand(MagicWand&& _Other) noexcept = delete;
	MagicWand& operator=(const MagicWand& _Other) = delete;
	MagicWand& operator=(MagicWand&& _Other) noexcept = delete;
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitCollision() override;
	void Action() override;
	void LevelUp() override;

	void Attack();

	void PopMagicWand();

	void SetFireRendererProperties(USpriteRenderer* _Renderer, int _SpriteNum, FVector2D _Pos);

	class AMonster* FindClosestMonster(const FVector2D& ActorLocation, const std::list<AMonster*>& Monsters);


protected:

private:
	std::deque<std::pair<int, USpriteRenderer*>> MagicWandRenderers;
	std::deque<class U2DCollision*> CollisionComponents;

	class APlayer* player = nullptr;
	class AMonsterSpawner* MonsterSpawner = nullptr;

	int EnterCount = 0;
};

