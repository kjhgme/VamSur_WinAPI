#pragma once
class ATitleSellectCharacter : public AActor
{
public:
	ATitleSellectCharacter();
	~ATitleSellectCharacter();

	ATitleSellectCharacter(const ATitleSellectCharacter& _Other) = delete;
	ATitleSellectCharacter(ATitleSellectCharacter&& _Other) noexcept = delete;
	ATitleSellectCharacter& operator=(const ATitleSellectCharacter& _Other) = delete;
	ATitleSellectCharacter& operator=(ATitleSellectCharacter&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

