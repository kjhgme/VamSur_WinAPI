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
	virtual void ChangeHeadDir();

protected:
	USpriteRenderer* IconSpriteRenderer = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	int Level = 0;

	bool HeadDirRight = true;
	bool Active = false;

private:
	FVector2D PlayerPos{0, 0};
};

