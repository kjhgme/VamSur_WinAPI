#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"

class AInGameMode : public AGameMode
{
public:
	AInGameMode();
	~AInGameMode();

	AInGameMode(const AInGameMode& _Other) = delete;
	AInGameMode(AInGameMode&& _Other) noexcept = delete;
	AInGameMode& operator=(const AInGameMode& _Other) = delete;
	AInGameMode& operator=(AInGameMode&& _Other) noexcept = delete;

	void BeginPlay();

	void SelectCharacter(std::string_view _name);

	void SpawnItemContainer();

	static APlayer* Player;

protected:

private:
};

