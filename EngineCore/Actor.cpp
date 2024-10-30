#include "PreCompile.h"
#include "Actor.h"

#include <EnginePlatform/EngineWinImage.h>
#include <EngineCore/EngineAPICore.h>

#include "EngineSprite.h"
#include "ImageManager.h"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::Render()
{
	if (nullptr == Sprite)
	{
		MSGASSERT("Actor's sprite don't setted.(AActor::Render)");
		return;
	}

	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();


	UEngineSprite::USpriteData CurData = Sprite->GetSpriteData(CurIndex);
	CurData.Image;
	CurData.Transform;
	CurData.Image->CopyToTrans(BackBufferImage, Transform, CurData.Transform);
}

void AActor::SetSprite(std::string_view _Name, int _CurIndex)
{
	Sprite = UImageManager::GetInst().FindSprite(_Name);

	if (nullptr == Sprite)
	{
		MSGASSERT("sprite is NULL.(AActor::SetSprite)" + std::string(_Name));
		return;
	}

	CurIndex = _CurIndex;
}