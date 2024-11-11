#pragma once
class WeaponSlotsUI : public AActor
{
public:
	WeaponSlotsUI();
	~WeaponSlotsUI();

	WeaponSlotsUI(const WeaponSlotsUI& _Other) = delete;
	WeaponSlotsUI(WeaponSlotsUI&& _Other) noexcept = delete;
	WeaponSlotsUI& operator=(const WeaponSlotsUI& _Other) = delete;
	WeaponSlotsUI& operator=(WeaponSlotsUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetPos();

protected:

private:
	FVector2D WindowSize{};
	FVector2D Pos{};
	FVector2D Scale{};
};

