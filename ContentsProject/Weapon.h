#pragma once
class AWeapon : public AActor
{
public:
	AWeapon();
	~AWeapon();

	AWeapon(const AWeapon& _Other) = delete;
	AWeapon(AWeapon&& _Other) noexcept = delete;
	AWeapon& operator=(const AWeapon& _Other) = delete;
	AWeapon& operator=(AWeapon&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void Action();

protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	int Level = 0;

private:
	FVector2D PlayerPos;
};

