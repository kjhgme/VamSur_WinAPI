#pragma once
class AInGameUI : public AActor
{
public:
	AInGameUI();
	~AInGameUI();

	AInGameUI(const AInGameUI& _Other) = delete;
	AInGameUI(AInGameUI&& _Other) noexcept = delete;
	AInGameUI& operator=(const AInGameUI& _Other) = delete;
	AInGameUI& operator=(AInGameUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
};

