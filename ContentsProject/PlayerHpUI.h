#pragma once
class PlayerHpUI : public AActor
{
public:
	PlayerHpUI();
	~PlayerHpUI();

	PlayerHpUI(const PlayerHpUI& _Other) = delete;
	PlayerHpUI(PlayerHpUI&& _Other) noexcept = delete;
	PlayerHpUI& operator=(const PlayerHpUI& _Other) = delete;
	PlayerHpUI& operator=(PlayerHpUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	USpriteRenderer* HpBarRenderer = nullptr;
	USpriteRenderer* HpBarFillRenderer = nullptr;

};

