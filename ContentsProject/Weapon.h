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
	Axe,
	KingBible,
	_Count,
};

//enum class PassiveWeaponType {
//	HollowHeart,
//	EmptyTome,
//	Bracer,
//	Candelabrador,
//	Spellbinder,
//	_Count,
//};

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

	// InitFunction
	virtual void InitCollision() {};

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

	// Function
	virtual void Action();
	virtual void ChangeHeadDir();
	virtual void LevelUp();

	void CollisionEnter(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);

	EWeaponType WeaponType;
	std::vector<WeaponLevelData> LevelDescriptions;
	int Level = 0;
	int AttackPower = 0;
	float KnockBack = 0;

protected:
	USpriteRenderer* IconSpriteRenderer = nullptr;
	USpriteRenderer* SpriteRenderer = nullptr;
	std::vector<U2DCollision*> CollisionComponents;

	bool HeadDirRight = true;

private:
	FVector2D PlayerPos{0, 0};

	USoundPlayer HitSoundPlayer;
};

