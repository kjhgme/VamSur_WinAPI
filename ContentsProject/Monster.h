#pragma once

#include <string.h>

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void MonsterInit();
	virtual void InitMonsterStatus() {};
	virtual void InitSprite() {};
	void InitCreateMonAnim();
	void InitCollision();

	// SetFunction
	void SetMonsterPos(FVector2D _pos);

	// Function
	virtual void ChasePlayer(float _DeltaTime);
	void ChangeAnimation();

protected:
	struct MonS {
		std::string Name;
		int Health{};
		int Power{};
		int Speed{};
		int KnockBack{};
		int KBMax{};
		int XP{};
	} MonsterStatus;
	
	class USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;

private:
	int MonsterKey{};
	bool HeadDirRight = false;
	bool Alive = true;
};

