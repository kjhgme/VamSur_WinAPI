#pragma once
#include <EngineCore/Actor.h>

class APlayMap : public AActor
{
public:
	APlayMap();
	APlayMap(int id) : id(id){}
	~APlayMap();

	APlayMap(const APlayMap& _Other) = delete;
	APlayMap(APlayMap&& _Other) noexcept = delete;
	APlayMap& operator=(const APlayMap& _Other) = delete;
	APlayMap& operator=(APlayMap&& _Other) noexcept = delete;

	void SetStage(int _level);

protected:

private:
	int id;
	USpriteRenderer* SpriteRenderer = nullptr;
};