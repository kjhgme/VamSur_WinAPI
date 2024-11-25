#pragma once
#include <EngineCore/GameMode.h>
#include "Player.h"
#include "MonsterSpawner.h"

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
	static AMonsterSpawner* MonsterSpawner;

protected:

private:
	class AInfiniteMap* Map = nullptr;
	class AInGameUI* InGameUI = nullptr;
};

