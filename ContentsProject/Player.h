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
		int Health{};
		int Armor{};
		int Might{};
		int Speed{ 160 };
	} PlayerStatus;

private:
	int MySpriteIndex = 0;
	bool HeadDirRight = true;

	class USpriteRenderer* SpriteRenderer = nullptr;
};

