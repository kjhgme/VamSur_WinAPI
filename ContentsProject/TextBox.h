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

	template<typename EnumType>
	void InitOrder(EnumType _Order)
	{
		InitOrder(static_cast<int>(_Order));
	}

	void InitOrder(int _Order)
	{
		Order = _Order;
	}

	void SetTextSpriteName(const std::string& _Text = "Letters");

	void SetTextScale(int _TextScale)
	{
		TextScale = { static_cast<float>(_TextScale), 2.0f * _TextScale };
	}

	void SetPos(FVector2D _Pos = {0.0f, 0.0f});

	void SetText(const std::string& _Text, const std::string& _Font = "Letters");

	void SetAlignLeft(bool _Align)
	{
		AlignLeft = _Align;
	}

	int MapCharacterToSpriteIndex(char Character);

protected:

private:
	FVector2D TextPos{};
	FVector2D TextScale{};
	int Order{};
	bool AlignLeft = true;

	std::string TextSpriteName;
	std::vector<class USpriteRenderer*> TextRenders;

	void SetSize(int _Size);

	void SetOrder();

};

