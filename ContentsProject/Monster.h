#pragma once
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

	// SetFunction
	virtual void SetSprite();
	virtual void SetMonsterStatus();
	void SetMonsterPos(FVector2D _pos);

	// Function
	virtual void ChasePlayer(float _DeltaTime);

protected:
	struct MonS {
		int Health{};
		int Power{};
		int Speed{};
		int KnockBack{};
		int KBMax{};
		int XP{};
	} MonsterStatus;

	class USpriteRenderer* SpriteRenderer = nullptr;

private:
	int MonsterKey{};
};

