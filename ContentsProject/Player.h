#pragma once
#include <EngineCore/Actor.h>

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

	APlayer* GetPlayer()
	{
		return this;
	}

	void PlayerMove(float _DeltaTime);

	void LevelChangeStart();
	void LevelChangeEnd();

protected:
	struct PSta {
		std::string Name;
		int Health = 0;
		int Armor = 0;
		int Might = 0;
		int Speed = 10;
	} PlayerStatus;
	
	class USpriteRenderer* SpriteRenderer = nullptr;

private:
	int MySpriteIndex = 0;
	bool HeadDirRight = true;

};

