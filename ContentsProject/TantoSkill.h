#pragma once
#include <deque>

struct DirectionCondition {
	bool HeadDirRight;
	bool HeadDirTop;
	bool HeadDirBottom;
	std::string SpriteName;
};

const std::vector<DirectionCondition> DirectionMapping = {
	{ true,  false, false, "Fire_00.png" },
	{ true,  false, true,  "Fire_01.png" },
	{ false, false, true,  "Fire_02.png" },
	{ false, false, true,  "Fire_03.png" },
	{ false, false, false, "Fire_04.png" },
	{ false, true,  false, "Fire_05.png" },
	{ false, true,  false, "Fire_06.png" },
	{ true,  true,  false, "Fire_07.png" },
};

class ATantoSkill : public AActor
{
public:
	ATantoSkill();
	~ATantoSkill();

	ATantoSkill(const ATantoSkill& _Other) = delete;
	ATantoSkill(ATantoSkill&& _Other) noexcept = delete;
	ATantoSkill& operator=(const ATantoSkill& _Other) = delete;
	ATantoSkill& operator=(ATantoSkill&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Fire();
	void PopFire();

	void SetFireRendererProperties(USpriteRenderer* _Renderer, const std::string& _SpriteName);
	void UpdateFire();

protected:

private:
	std::deque<USpriteRenderer*> FireRenderers;
	std::deque< U2DCollision*> CollisionComponents;
	float Time = 0.0f;
	bool PopStart = false;

	class APlayer* player = nullptr;
};

