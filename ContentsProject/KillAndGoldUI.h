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

	void SetTextSpriteName(const std::string _Text);

	void SetTextScale(FVector2D _TextScale)
	{
		TextScale = _TextScale;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetDisplay();

	void SetPos();

	void DisplayKillCount();
	void DisplayGoldCount();

	void AddKillCount();
	void AddGoldCount(int _Gold);

protected:

private:
	FVector2D WindowSize{};
	FVector2D Pos{};

	int KillCount = 0;
	int GoldCount = 0;

	FVector2D TextScale{};
	std::string TextSpriteName;
	std::vector<class USpriteRenderer*> KillRenders;
	std::vector<class USpriteRenderer*> GoldRenders;
};

