#pragma once
class ExpBarUI : public AActor
{
public:
	ExpBarUI();
	~ExpBarUI();

	ExpBarUI(const ExpBarUI& _Other) = delete;
	ExpBarUI(ExpBarUI&& _Other) noexcept = delete;
	ExpBarUI& operator=(const ExpBarUI& _Other) = delete;
	ExpBarUI& operator=(ExpBarUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetPos();

protected:

private:
	FVector2D WindowSize{};
	FVector2D Pos{};
	FVector2D Scale{};
};

