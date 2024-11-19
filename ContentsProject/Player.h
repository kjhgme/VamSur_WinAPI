#pragma once
#include <unordered_map>

#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>
#include "CharactersStatus.h"
#include "Weapon.h"

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

	AWeapon* GetWeapon()
	{
		return Weapons[0];
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
	float GetNextLevelXP(int currentLevel);

	static CharacterStatus PlayerStatus;

protected:

private:
	bool HeadDirRight = true;

	AWeapon* Weapons[6]{};
	AWeapon* PassiveWeapons[6]{};

	std::unordered_map<AActor*, float> CollisionStayTimers;

	class USpriteRenderer* SpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* BloodRenderer = nullptr;
};

