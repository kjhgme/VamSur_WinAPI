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

protected:

private:

};

