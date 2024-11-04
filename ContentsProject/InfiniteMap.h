#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include "PlayMap.h"
#include "Player.h"

class AInfiniteMap : public AActor
{
public:
	AInfiniteMap();
	~AInfiniteMap();

	AInfiniteMap(const AInfiniteMap& _Other) = delete;
	AInfiniteMap(AInfiniteMap&& _Other) noexcept = delete;
	AInfiniteMap& operator=(const AInfiniteMap& _Other) = delete;
	AInfiniteMap& operator=(AInfiniteMap&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;

	void SetStage(USpriteRenderer* _SpriteRenderer, int _level);

	void InitMaps();
	void MapMoveCheck(FVector2D _PlayerPos);

protected:

private:
	FVector2D playerPos {};
	FVector2D MapScale{};
	FVector2D InfiMapPos{ 1, 1 };
	APlayMap* Map = nullptr;
	UEngineAPICore* core = nullptr;
	std::vector<std::vector<USpriteRenderer*>> InfiMap;
};