#pragma once
#include <EngineCore/GameMode.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

class AResultGameMode : public AGameMode
{
public:
	AResultGameMode();
	~AResultGameMode();

	AResultGameMode(const AResultGameMode& _Other) = delete;
	AResultGameMode(AResultGameMode&& _Other) noexcept = delete;
	AResultGameMode& operator=(const AResultGameMode& _Other) = delete;
	AResultGameMode& operator=(AResultGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

