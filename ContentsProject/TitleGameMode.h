#pragma once
#include <EngineCore/GameMode.h>

enum CharacterName
{
	None = 0,
	Antonio,
	Imelda,
};

class ATitleGameMode : public AGameMode
{
public:
	ATitleGameMode();
	~ATitleGameMode();

	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	static CharacterName SelectedCharacter;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void TitleInit();
};

