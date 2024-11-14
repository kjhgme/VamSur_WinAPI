#pragma once
class ADropItem : public AActor
{
public:
	ADropItem();
	~ADropItem();

	ADropItem(const ADropItem& _Other) = delete;
	ADropItem(ADropItem&& _Other) noexcept = delete;
	ADropItem& operator=(const ADropItem& _Other) = delete;
	ADropItem& operator=(ADropItem&& _Other) noexcept = delete;

	void SetLocation(FVector2D _Pos);

protected:
	USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D Pos{};

private:

};

