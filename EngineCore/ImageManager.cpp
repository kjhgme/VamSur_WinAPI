#include "PreCompile.h"
#include "ImageManager.h"

#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineAPICore.h>

UImageManager::UImageManager()
{
}

UImageManager::~UImageManager()
{
}

void UImageManager::Load(std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);

	std::string FileName = EnginePath.GetFileName();

	Load(FileName, Path);
}

void UImageManager::Load(std::string_view _KeyName, std::string_view Path)
{
	UEnginePath EnginePath = UEnginePath(Path);

	if (true == EnginePath.IsDirectory())
	{
		MSGASSERT("Path's directory load fail.(UImageManager::Load)" + std::string(Path));
		return;
	}

	if (false == EnginePath.IsExists())
	{
		MSGASSERT("Path is not exist.(UImageManager::Load)" + std::string(Path));
		return;
	}

	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->Load(WindowImage, Path);

	Images.insert({ UpperName , NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();

	FTransform Transform;
	Transform.Location = { 0,0 };
	Transform.Scale = NewImage->GetImageScale();

	NewSprite->PushData(NewImage, Transform);

	Sprites.insert({ UpperName , NewSprite });
}

bool UImageManager::IsLoadSprite(std::string_view _KeyName)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	return Sprites.contains(UpperName);
}

UEngineSprite* UImageManager::FindSprite(std::string_view _KeyName)
{
	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (false == Sprites.contains(UpperName))
	{
		MSGASSERT("Sprite is NULL.(UImageManager::FindSprite)" + std::string(_KeyName));
		return nullptr;
	}

	return Sprites[UpperName];
}