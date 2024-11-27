#pragma once
#include <vector>

#include <EngineCore/Actor.h>
#include "Player.h"

class AInfiniteMap : public AActor
{
public:
	AInfiniteMap() {};
	AInfiniteMap(int _level) : StageLevel(_level) {};
	~AInfiniteMap();

	AInfiniteMap(const AInfiniteMap& _Other) = delete;
	AInfiniteMap(AInfiniteMap&& _Other) noexcept = delete;
	AInfiniteMap& operator=(const AInfiniteMap& _Other) = delete;
	AInfiniteMap& operator=(AInfiniteMap&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetStage(USpriteRenderer* _SpriteRenderer, int _level);

	void InitMaps(int _level);
	void MapMoveCheck(FVector2D _PlayerPos);

protected:

private:
	int StageLevel = 0;
	FVector2D playerPos {};
	FVector2D MapScale{};
	FVector2D InfiMapPos{ 1, 1 };
	UEngineAPICore* core = nullptr;
	std::vector<std::vector<USpriteRenderer*>> InfiMap;
};