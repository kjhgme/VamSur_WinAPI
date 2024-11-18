#pragma once

#include "LevelUpUI.h"
#include "KillAndGoldUI.h"

class AInGameUI : public AActor
{
public:
	AInGameUI();
	~AInGameUI();

	AInGameUI(const AInGameUI& _Other) = delete;
	AInGameUI(AInGameUI&& _Other) noexcept = delete;
	AInGameUI& operator=(const AInGameUI& _Other) = delete;
	AInGameUI& operator=(AInGameUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	static LevelUpUI* LevelUpPanel;
	static KillAndGoldUI* KillAndGold;

protected:

private:
};

