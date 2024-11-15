#pragma once
class LevelUpUI : public AActor
{
public:
	LevelUpUI();
	~LevelUpUI();

	LevelUpUI(const LevelUpUI& _Other) = delete;
	LevelUpUI(LevelUpUI&& _Other) noexcept = delete;
	LevelUpUI& operator=(const LevelUpUI& _Other) = delete;
	LevelUpUI& operator=(LevelUpUI&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	void SetPos();

	void SetActive();

protected:

private:
	USpriteRenderer* SpriteRenderer = nullptr;

	FVector2D WindowSize{};
	FVector2D Pos{};
	FVector2D Scale{};
};

