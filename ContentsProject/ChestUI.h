#pragma once
class ChestUI : public AActor
{
public:
	ChestUI();
	~ChestUI();

	ChestUI(const ChestUI& _Other) = delete;
	ChestUI(ChestUI&& _Other) noexcept = delete;
	ChestUI& operator=(const ChestUI& _Other) = delete;
	ChestUI& operator=(ChestUI&& _Other) noexcept = delete;

	void OpenChest();
	void GetWeapon();

protected:

private:
	class USpriteRenderer* PanelRenderer = nullptr;
	class USpriteRenderer* ChestRenderer = nullptr;
};

