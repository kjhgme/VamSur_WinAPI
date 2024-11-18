#pragma once
class ATimeUI : public AActor
{
public:
	ATimeUI();
	~ATimeUI();

	ATimeUI(const ATimeUI& _Other) = delete;
	ATimeUI(ATimeUI&& _Other) noexcept = delete;
	ATimeUI& operator=(const ATimeUI& _Other) = delete;
	ATimeUI& operator=(ATimeUI&& _Other) noexcept = delete;

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

	void SetValue(int _Score);

	void SetPos();
	void SetDisplayTime(float _DeltaTime);

protected:

private:
	FVector2D WindowSize{};
	FVector2D Scale{};
	FVector2D Pos{};

	float Time{};
	int Minutes{};
	int Seconds{};

	FVector2D TextScale{};
	std::string TextSpriteName;
	std::vector<class USpriteRenderer*> Renders;
};

