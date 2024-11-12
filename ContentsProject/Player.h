#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>
#include "CharactersStatus.h"

class APlayer : public AActor
{
public:
	APlayer();
	~APlayer();

	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void PlayerInit(std::string_view _Name);
	void InitPlayerStatus(std::string_view _name);
	void InitSprite(std::string_view _name);
	void InitCreatePlayerAnim();
	void InitCollision();

	APlayer* GetPlayer()
	{
		return this;
	}

	void PlayerMove(float _DeltaTime);

	void LevelChangeStart();
	void LevelChangeEnd();

	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

protected:
	CharacterStatus PlayerStatus;
	
	class USpriteRenderer* SpriteRenderer = nullptr;

private:
	int MySpriteIndex = 0;
	bool HeadDirRight = true;

	U2DCollision* CollisionComponent = nullptr;

	static const std::unordered_map<std::string_view, const CharacterStatus*> characterStatusMap;
};

