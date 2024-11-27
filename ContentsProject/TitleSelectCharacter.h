#pragma once
class ATitleSelectCharacter : public AActor
{
public:
	ATitleSelectCharacter();
	~ATitleSelectCharacter();

	ATitleSelectCharacter(const ATitleSelectCharacter& _Other) = delete;
	ATitleSelectCharacter(ATitleSelectCharacter&& _Other) noexcept = delete;
	ATitleSelectCharacter& operator=(const ATitleSelectCharacter& _Other) = delete;
	ATitleSelectCharacter& operator=(ATitleSelectCharacter&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	std::vector<int> Characters;
};

