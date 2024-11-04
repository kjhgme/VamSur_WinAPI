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


protected:

private:
	// USpriteRenderer* SpriteRenderer = nullptr;
	FVector2D playerPos {};
	FVector2D MapScale{};
	APlayMap* Map = nullptr;
	UEngineAPICore* core = nullptr;
	std::vector<USpriteRenderer*> InfiMap;
};