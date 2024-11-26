#pragma once
#include <EngineCore/2DCollision.h>
#include <EnginePlatform/EngineSound.h>

struct WeaponLevelData {
	int Level;
	std::string Description;

	WeaponLevelData()
		: Level(1), Description("Default Description") {}

	WeaponLevelData(int InLevel, const std::string& InDescription)
		: Level(InLevel), Description(InDescription) {}
};

enum class EWeaponType : int {
	Whip,
	MagicWand,
	Knife,
	FireWand,
	KingBible,
	Garlic,
	HollowHeart,
	EmptyTome,
	Bracer,
	Spinach,
	Spellbinder,
	Pummarola,
	TotalCount,
	BigCoinBag,
	FloorChicken,
};

class AWeapon : public AActor
{
public:
	AWeapon() {};
	~AWeapon() {};

	AWeapon(const AWeapon& _Other) = delete;
	AWeapon(AWeapon&& _Other) noexcept = delete;
	AWeapon& operator=(const AWeapon& _Other) = delete;
	AWeapon& operator=(AWeapon&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// GetFunction
	std::string GetWeaponDescriptionByLevel(int _Level) const
	{
		for (const auto& Data : LevelDescriptions)
		{
			if (Data.Level == _Level)
			{
				return Data.Description;
			}
		}
		return "Unknown Level...";
	}

	USpriteRenderer* GetIconSpriteRenderer()
	{
		return IconSpriteRenderer;
	}

	FVector2D GetPlayerPosition()
	{
		return PlayerPos;
	}

	// Function
	virtual void Action();
	virtual void ChangeHeadDir();
	virtual void LevelUp();

	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

	EWeaponType WeaponType = EWeaponType::TotalCount;
	std::vector<WeaponLevelData> LevelDescriptions;

	int Level = 0;
	float AttackPower = 0.0f;
	int Amount = 0;
	float KnockBack = 0.0f;
	float Area = 100.0f;
	float Speed = 100.0f;
	float Cooldown = 0.0f;
	float Recovery = 0.0f;
	float Duration = 0.0f;
	float Health = 0.0f;

protected:
	USpriteRenderer* IconSpriteRenderer = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	std::vector<U2DCollision*> CollisionComponents;

	bool HeadDirRight = true;

private:
	FVector2D PlayerPos{0, 0};

	USoundPlayer HitSoundPlayer;
};

