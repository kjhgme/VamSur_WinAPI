#include "PreCompile.h"
#include "ImageManager.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineString.h>
#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineAPICore.h>

UImageManager::UImageManager()
{
}

UImageManager::~UImageManager()
{
	{
		std::map<std::string, UEngineWinImage*>::iterator StartIter = Images.begin();
		std::map<std::string, UEngineWinImage*>::iterator EndIter = Images.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			UEngineWinImage* CurRes = StartIter->second;
			if (nullptr != CurRes)
			{
				delete CurRes;
				CurRes = nullptr;
			}
		}
	}

	{
		std::map<std::string, UEngineSprite*>::iterator StartIter = Sprites.begin();
		std::map<std::string, UEngineSprite*>::iterator EndIter = Sprites.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			UEngineSprite* CurRes = StartIter->second;
			if (nullptr != CurRes)
			{
				delete CurRes;
				CurRes = nullptr;
			}
		}
	}
}

void UImageManager::Load(std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);

	std::string FileName = EnginePath.GetFileName();

	Load(FileName, _Path);
}

void UImageManager::Load(std::string_view _KeyName, std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);

	if (true == EnginePath.IsDirectory())
	{
		MSGASSERT("Path's directory load fail.(UImageManager::Load)" + std::string(_Path));
		return;
	}

	if (false == EnginePath.IsExists())
	{
		MSGASSERT("Path is not exist.(UImageManager::Load)" + std::string(_Path));
		return;
	}

	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	UEngineWinImage* NewImage = new UEngineWinImage();
	NewImage->Load(WindowImage, _Path);

	Images.insert({ UpperName , NewImage });

	UEngineSprite* NewSprite = new UEngineSprite();

	FTransform Transform;
	Transform.Location = { 0,0 };
	Transform.Scale = NewImage->GetImageScale();

	NewSprite->PushData(NewImage, Transform);

	Sprites.insert({ UpperName , NewSprite });
}

void UImageManager::LoadFolder(std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);

	std::string DirName = EnginePath.GetDirectoryName();

	LoadFolder(DirName, _Path);
}

void UImageManager::LoadFolder(std::string_view _KeyName, std::string_view _Path)
{
	UEnginePath EnginePath = UEnginePath(_Path);

	if (false == EnginePath.IsExists())
	{
		MSGASSERT("EnginePath is not exist." + std::string(_Path));
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_KeyName);

	if (true == Sprites.contains(UpperName))
	{
		MSGASSERT("Image is not contained." + UpperName);
		return;
	}


	UEngineSprite* NewSprite = new UEngineSprite();
	NewSprite->SetName(UpperName);
	Sprites.insert({ UpperName , NewSprite });

	UEngineWinImage* WindowImage = UEngineAPICore::GetCore()->GetMainWindow().GetWindowImage();

	UEngineDirectory Dir = _Path;
	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		std::string UpperFileName = UEngineString::ToUpper(ImageFiles[i].GetFileName());

		UEngineWinImage* NewImage = FindImage(UpperFileName);
		if (nullptr == NewImage)
		{
			NewImage = new UEngineWinImage();
			NewImage->SetName(UpperFileName);
			NewImage->Load(WindowImage, FilePath);
		}
		Images.insert({ UpperFileName,  NewImage });

		FTransform Transform;
		Transform.Location = { 0, 0 };
		Transform.Scale = NewImage->GetImageScale();

		NewSprite->PushData(NewImage, Transform);
	}
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

UEngineWinImage* UImageManager::FindImage(std::string_view _KeyName)
{
	return nullptr;
}
