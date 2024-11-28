#pragma once
#include <unordered_map>

#include <EngineCore/Actor.h>
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

	// GetFunction
	static int GetLevel()
	{
		return PlayerStatus.Level;
	}

	class AWeaponManager* GetWeaponManager()
	{
		return WeaponManager;
	}

	FVector2D GetPlayerScale() const
	{		
		return SpriteRenderer->GetComponentScale();
	}

	bool GetHeadDirRight()
	{
		return HeadDirRight;
	}
	bool GetHeadDirTop()
	{
		return HeadDirTop;
	}
	bool GetHeadDirBottom()
	{
		return HeadDirBottom;
	}
	bool GetHeadDirStationary()
	{
		return HeadDirStationary;
	}

	// Function
	void PlayerMove(float _DeltaTime);

	void LevelChangeStart();
	void LevelChangeEnd();

	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

	void TakeDamage(AActor* _ColActor);
	void Die();

	void AddExp(float _add);
	void LevelUp();
	void UpdateMaxExp();

	void AddHp(float _add);

	static CharacterStatus PlayerStatus;

protected:

private:
	bool HeadDirRight = true;
	bool HeadDirStationary = true;
	bool HeadDirTop = false;
	bool HeadDirBottom = false;
	bool Alive = true;

	float DieScale = 1.0f;

	std::unordered_map<AActor*, float> CollisionStayTimers;

	class AWeaponManager* WeaponManager = nullptr;

	class USpriteRenderer* SpriteRenderer = nullptr;
	class U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* BloodRenderer = nullptr;
};

