#pragma once
class KillAndGoldUI : public AActor
{
public:
	KillAndGoldUI();
	~KillAndGoldUI();

	KillAndGoldUI(const KillAndGoldUI& _Other) = delete;
	KillAndGoldUI(KillAndGoldUI&& _Other) noexcept = delete;
	KillAndGoldUI& operator=(const KillAndGoldUI& _Other) = delete;
	KillAndGoldUI& operator=(KillAndGoldUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetPos();

protected:

private:
	FVector2D WindowSize{};
	FVector2D Pos{};
};

