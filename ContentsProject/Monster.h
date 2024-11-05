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

	void MonsterInit(FVector2D _pos);
	void SpriteSetting();
	virtual void ChasePlayer(float _DeltaTime);

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;

	int MonsterKey{};

	int Health{};
	int Power{};
	int Speed{ 1 };
	int KnockBack{};
	int KBMax{};
	int XP{};
};

