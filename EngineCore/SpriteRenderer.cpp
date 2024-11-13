#include "PreCompile.h"
#include "SpriteRenderer.h"

#include <EngineBase/EngineString.h>

#include "EngineAPICore.h"
#include "ImageManager.h"

USpriteRenderer::USpriteRenderer()
{
}

USpriteRenderer::~USpriteRenderer()
{
}

void USpriteRenderer::BeginPlay()
{
	Super::BeginPlay();

	AActor* Actor = GetActor();
	ULevel* Level = Actor->GetWorld();

 	Level->PushRenderer(this);
}

void USpriteRenderer::ComponentTick(float _DeltaTime)
{
	Super::ComponentTick(_DeltaTime);
}

void USpriteRenderer::Render(float _DeltaTime)
{
	if (nullptr != CurAnimation)
	{
		std::vector<int>& Indexs = CurAnimation->FrameIndex;
		std::vector<float>& Times = CurAnimation->FrameTime;

		Sprite = CurAnimation->Sprite;

		CurAnimation->CurTime += _DeltaTime;

		float CurFrameTime = Times[CurAnimation->CurIndex];

		if (CurAnimation->CurTime > CurFrameTime)
		{
			CurAnimation->CurTime -= CurFrameTime;
			++CurAnimation->CurIndex;

			if (CurAnimation->Events.contains(CurAnimation->CurIndex))
			{
				CurAnimation->Events[CurAnimation->CurIndex]();
			}

			if (CurAnimation->CurIndex >= Indexs.size())
			{
				if (true == CurAnimation->Loop)
				{
					CurAnimation->CurIndex = 0;

					if (CurAnimation->Events.contains(CurAnimation->CurIndex))
					{
						CurAnimation->Events[CurAnimation->CurIndex]();
					}

				}
				else
				{
					--CurAnimation->CurIndex;
				}
			}

		}

		CurIndex = Indexs[CurAnimation->CurIndex];
	}

	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is NULL.(USpriteRenderer::Render)");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);

	FTransform Trans = GetActorTransform();

	ULevel* Level = GetActor()->GetWorld();

	Trans.Location = Trans.Location - Level->CameraPos;

	if (Alpha == 255)
	{
		CurData.Image->CopyToTrans(BackBufferImage, Trans, CurData.Transform);
	}
	else
	{
		CurData.Image->CopyToAlpha(BackBufferImage, Trans, CurData.Transform, Alpha);
	}
}

void USpriteRenderer::SetOrder(int _Order)
{
	int PrevOrder = Order;
	Order = _Order;

	ULevel* Level = GetActor()->GetWorld();

	if (nullptr != Level)
	{
		Level->ChangeRenderOrder(this, PrevOrder);
	}
}

void USpriteRenderer::SetSprite(std::string_view _Name, int _CurIndex)
{
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is NULL.(USpriteRenderer::SetSprite)" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}

void USpriteRenderer::SetAnimationEvent(std::string_view _AnimationName, int _Frame, std::function<void()> _Function)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("Animation is not exist.(USpriteRenderer::SetAnimationEvent)" + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	bool Check = false;

	for (size_t i = 0; i < ChangeAnimation->FrameIndex.size(); i++)
	{
		if (_Frame == ChangeAnimation->FrameIndex[i])
		{
			Check = true;
			break;
		}
	}

	if (false == Check)
	{
		MSGASSERT("Frame is not exist.(USpriteRenderer::SetAnimationEvent)" + std::string(_AnimationName));
		return;
	}

	ChangeAnimation->Events[_Frame] += _Function;

}

FVector2D USpriteRenderer::SetSpriteScale(float _Ratio, int _CurIndex)
{
	if (nullptr == Sprite)
	{
		MSGASSERT("Sprite is NULL.( USpriteRenderer::SetSpriteScale)");
		return FVector2D::ZERO;
	}

	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(_CurIndex);
	FVector2D Scale = CurData.Transform.Scale * _Ratio;
	SetComponentScale(CurData.Transform.Scale * _Ratio);

	return Scale;
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, int _Start, int _End, float Time, bool _Loop)
{
	if (_Start > _End)
	{
		MSGASSERT("End is bigger than start.(USpriteRenderer::CreateAnimation)" + std::string(_AnimationName));
		return;
	}

	int Inter = (_End - _Start) + 1;

	std::vector<int> Indexs;
	std::vector<float> Times;

	for (size_t i = 0; i < Inter; i++)
	{
		Indexs.push_back(_Start);
		Times.push_back(Time);
		++_Start;
	}

	CreateAnimation(_AnimationName, _SpriteName, Indexs, Times, _Loop);

}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, float _Frame, bool _Loop)
{
	std::vector<float> Times;

	for (size_t i = 0; i < _Indexs.size(); i++)
	{
		Times.push_back(_Frame);
	}

	CreateAnimation(_AnimationName, _SpriteName, _Indexs, Times, _Loop);
}

void USpriteRenderer::CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<int> _Indexs, std::vector<float> _Frame, bool _Loop)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (_Frame.size() != _Indexs.size())
	{
		MSGASSERT("Frame.size is not same _Indexs.size.(USpriteRenderer::CreateAnimation)" + UpperName);
		return;
	}

	if (FrameAnimations.contains(UpperName))
	{
		return;
	}

	UEngineSprite* FindSprite = UImageManager::GetInst().FindSprite(_SpriteName);

	if (nullptr == FindSprite)
	{
		MSGASSERT("Sprite is not found.(USpriteRenderer::CreateAnimation)" + UpperName);
		return;
	}

	FrameAnimation NewAnimation;
	NewAnimation.Sprite = FindSprite;
	NewAnimation.FrameIndex = _Indexs;
	NewAnimation.FrameTime = _Frame;
	NewAnimation.Loop = _Loop;
	NewAnimation.Reset();

	FrameAnimations.insert({ UpperName ,NewAnimation });
}

void USpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force)
{
	std::string UpperName = UEngineString::ToUpper(_AnimationName);

	if (false == FrameAnimations.contains(UpperName))
	{
		MSGASSERT("Animation is not exist.(USpriteRenderer::ChangeAnimation)" + UpperName);
		return;
	}

	FrameAnimation* ChangeAnimation = &FrameAnimations[UpperName];

	if (CurAnimation == ChangeAnimation && false == _Force)
	{
		return;
	}

	CurAnimation = &FrameAnimations[UpperName];
	CurAnimation->Reset();

	if (CurAnimation->Events.contains(CurAnimation->CurIndex))
	{
		CurAnimation->Events[CurAnimation->CurIndex]();
	}

	Sprite = CurAnimation->Sprite;
}

