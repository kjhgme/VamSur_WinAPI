#include "PreCompile.h"
#include "Level.h"

#include <EnginePlatform/EngineWinImage.h>

#include "EngineAPICore.h"
#include "SpriteRenderer.h"

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			delete CurActor;
		}
	}

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			if (nullptr != CurActor)
			{
				delete* StartIter;
			}
		}
	}
}

void ULevel::Tick(float _DeltaTime)
{
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->BeginPlay();
			AllActors.push_back(CurActor);
		}

		BeginPlayList.clear();

		AActor::ComponentBeginPlay();
	}

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			CurActor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	ScreenClear();

	if (true == IsCameraToMainPawn)
	{
		// CameraPivot = FVector2D(-1280, -720) * 0.5f;
		CameraPos = MainPawn->GetTransform().Location + CameraPivot;
	}

	std::map<int, std::list<class USpriteRenderer*>>::iterator StartOrderIter = Renderers.begin();
	std::map<int, std::list<class USpriteRenderer*>>::iterator EndOrderIter = Renderers.end();

	for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
	{
		std::list<class USpriteRenderer*>& RendererList = StartOrderIter->second;

		std::list<class USpriteRenderer*>::iterator RenderStartIter = RendererList.begin();
		std::list<class USpriteRenderer*>::iterator RenderEndIter = RendererList.end();

		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			(*RenderStartIter)->Render(_DeltaTime);
		}

	}

	DoubleBuffering();
}

void ULevel::LevelChangeStart()
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		CurActor->LevelChangeStart();
	}	
}

void ULevel::LevelChangeEnd()
{	
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		CurActor->LevelChangeEnd();
	}	
}

// private
void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -2, -2, Size.iX() + 2, Size.iY() + 2);
}

void ULevel::DoubleBuffering()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	FTransform Transform;
	Transform.Location = MainWindow.GetWindowSize().Half();
	Transform.Scale = MainWindow.GetWindowSize();

	BackBufferImage->CopyToBit(WindowImage, Transform);
}

void ULevel::PushRenderer(USpriteRenderer* _Renderer)
{
	int Order = _Renderer->GetOrder();

	Renderers[Order].push_back(_Renderer);
}

void ULevel::ChangeRenderOrder(USpriteRenderer* _Renderer, int _PrevOrder)
{
	Renderers[_PrevOrder].remove(_Renderer);

	Renderers[_Renderer->GetOrder()].push_back(_Renderer);
}
