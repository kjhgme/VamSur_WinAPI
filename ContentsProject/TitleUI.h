#pragma once
class ATitleUI : public AActor
{
public:
	ATitleUI();
	~ATitleUI();

	ATitleUI(const ATitleUI& _Other) = delete;
	ATitleUI(ATitleUI&& _Other) noexcept = delete;
	ATitleUI& operator=(const ATitleUI& _Other) = delete;
	ATitleUI& operator=(ATitleUI&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
};

