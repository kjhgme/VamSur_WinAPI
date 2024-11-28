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

	void Opening();

protected:

private:
	class USpriteRenderer* TopPanel = nullptr;
	class USpriteRenderer* BackButton = nullptr;
	class USpriteRenderer* MoneyPanel = nullptr;
	class USpriteRenderer* OptionButton = nullptr;
	class USpriteRenderer* StartButton = nullptr;
	class USpriteRenderer* CollectionButton = nullptr;
	class USpriteRenderer* UpgradeButton = nullptr;
	class USpriteRenderer* UnlockButton = nullptr;
	class USpriteRenderer* MakerButton = nullptr;
	class ATitleCursor* Cursor = nullptr;
};

