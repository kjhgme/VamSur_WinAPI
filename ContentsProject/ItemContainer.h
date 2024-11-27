#pragma once
class AItemContainer : public AActor
{
public:
	AItemContainer();
	~AItemContainer();

	AItemContainer(const AItemContainer& _Other) = delete;
	AItemContainer(AItemContainer&& _Other) noexcept = delete;
	AItemContainer& operator=(const AItemContainer& _Other) = delete;
	AItemContainer& operator=(AItemContainer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionEnter(AActor* _ColActor);

	void ChangeIdle();

	void SpawnDropItem();

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	class U2DCollision* CollisionComponent = nullptr;

	float Hp = 10.0f;
};

