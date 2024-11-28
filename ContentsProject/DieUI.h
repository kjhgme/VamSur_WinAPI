#pragma once
class DieUI : public AActor
{
public:
	DieUI();
	~DieUI();

	DieUI(const DieUI& _Other) = delete;
	DieUI(DieUI&& _Other) noexcept = delete;
	DieUI& operator=(const DieUI& _Other) = delete;
	DieUI& operator=(DieUI&& _Other) noexcept = delete;

protected:

private:
	class USpriteRenderer* GameOverRenderer = nullptr;
	class USpriteRenderer* BackGroundRenderer = nullptr;
	class USpriteRenderer* BackButtonRenderer = nullptr;
	class USpriteRenderer* LeftCursorRenderer = nullptr;
	class USpriteRenderer* RightCursorRenderer = nullptr;

	float GameOverAlpha = 0.0f;
	float BackGroundAlpha = 0.0f;
	float BackGroundScale = 2.0f;
	float ButtonScale = 0.0f;

	void UIAnimation();
};

