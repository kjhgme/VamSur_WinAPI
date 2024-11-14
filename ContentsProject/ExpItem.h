#pragma once
class AExpItem : public AActor
{
public:
	AExpItem();
	~AExpItem();

	AExpItem(const AExpItem& _Other) = delete;
	AExpItem(AExpItem&& _Other) noexcept = delete;
	AExpItem& operator=(const AExpItem& _Other) = delete;
	AExpItem& operator=(AExpItem&& _Other) noexcept = delete;

	void SetLocation(FVector2D _Pos);

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Pos{};
};

