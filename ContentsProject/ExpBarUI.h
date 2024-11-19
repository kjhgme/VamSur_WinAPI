#pragma once

#include "TextBox.h"

class ExpBarUI : public AActor
{
public:
	ExpBarUI();
	~ExpBarUI();

	ExpBarUI(const ExpBarUI& _Other) = delete;
	ExpBarUI(ExpBarUI&& _Other) noexcept = delete;
	ExpBarUI& operator=(const ExpBarUI& _Other) = delete;
	ExpBarUI& operator=(ExpBarUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetPos();
	void SetPlayerLevel();

protected:

private:
	FVector2D WindowSize{};
	FVector2D Pos{};
	FVector2D Scale{};

	int PlayerLevel = 1;

	ATextBox* LevelText = nullptr;
};

