#pragma once
class ATextBox : public AActor
{
public:
	ATextBox();
	~ATextBox();

	ATextBox(const ATextBox& _Other) = delete;
	ATextBox(ATextBox&& _Other) noexcept = delete;
	ATextBox& operator=(const ATextBox& _Other) = delete;
	ATextBox& operator=(ATextBox&& _Other) noexcept = delete;
	
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

	void SetPos(FVector2D _Pos = {0.0f, 0.0f});

	void SetText(std::string_view _Text);
	void SetSize(int _Size);

	int MapCharacterToSpriteIndex(char Character);

protected:

private:
	FVector2D Pos{};
	FVector2D TextScale{};

	std::string TextSpriteName;
	std::vector<class USpriteRenderer*> TextRenders;
};

