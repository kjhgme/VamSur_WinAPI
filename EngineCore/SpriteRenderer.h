#pragma once
#include <map>

#include <EngineBase/EngineDelegate.h>

#include "SceneComponent.h"
#include "EngineSprite.h"

class USpriteRenderer : public USceneComponent
{
public:
	class FrameAnimation
	{
	public:
		UEngineSprite* Sprite = nullptr;
		std::vector<int> FrameIndex;
		std::vector<float> FrameTime;
		std::map<int, EngineDelegate> Events;

		int CurIndex = 0;
		int ResultIndex = 0;
		float CurTime = 0.0f;
		bool Loop = true;

		void Reset()
		{
			CurIndex = 0;
			CurTime = 0;
			ResultIndex = 0;
		}
	};

	USpriteRenderer();
	~USpriteRenderer();

	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;
	void Render(float _DeltaTime);

	// GetFunction
	int GetOrder()
	{
		return Order;
	}

	std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	// SetFunction
	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}

	void SetOrder(int _Order);

	void SetSprite(std::string_view _Name, int _CurIndex = 0);
	void SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function);
	
	FVector2D SetSpriteScale(float _Ratio = 1.0f, int _CurIndex = 0);
		
	// Function
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time = 0.1f, bool _Loop = true);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop = true);
	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false);

protected:

private:
	int Order = 0;
	int CurIndex = 0;

	class UEngineSprite* Sprite = nullptr;
	
	std::map<std::string, FrameAnimation> FrameAnimations;
	FrameAnimation* CurAnimation = nullptr;
	
};

