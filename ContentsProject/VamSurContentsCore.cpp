#include "PreCompile.h"
#include "VamSurContentsCore.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "InGameMode.h"
#include "ResultGameMode.h"
#include "Player.h"

VamSurContentsCore::VamSurContentsCore()
{
}

VamSurContentsCore::~VamSurContentsCore()
{
}

void VamSurContentsCore::BeginPlay()
{
	// ImageLoad
	{
		// Title
		{
			UEngineDirectory TitleDir;
			if (false == TitleDir.MoveParentToDirectory("Resources/Title"))
			{
				MSGASSERT("Resources folder is not exist.(VamSurContentsCore::BeginPlay)");
				return;
			}

			std::vector<UEngineFile> ImageFiles = TitleDir.GetAllFile();

			for (size_t i = 0; i < ImageFiles.size(); i++)
			{
				std::string FilePath = ImageFiles[i].GetPathToString();
				UImageManager::GetInst().Load(FilePath);
			}
		}
		// UI
		{
			UEngineDirectory UIDir;
			UIDir.MoveParentToDirectory("Resources/UI");
			UIDir.Append("Cursor");

			UImageManager::GetInst().LoadFolder(UIDir.GetPathToString());
		}
		// Charcters
		{
			UEngineDirectory CharacterDir;
			CharacterDir.MoveParentToDirectory("Resources/Characters");
			CharacterDir.Append("Antonio");

			UImageManager::GetInst().LoadFolder(CharacterDir.GetPathToString());

			CharacterDir.MoveParentToDirectory("Resources/Characters");
			CharacterDir.Append("Imelda");

			UImageManager::GetInst().LoadFolder(CharacterDir.GetPathToString());

		}
		// Stage
		{
			UEngineDirectory StageDir;
			StageDir.MoveParentToDirectory("Resources");
			StageDir.Append("Stage");

			UImageManager::GetInst().LoadFolder(StageDir.GetPathToString());
		}
		// Monster
		{
			UEngineDirectory MonsterLDir;
			MonsterLDir.MoveParentToDirectory("Resources/Monster_L");
			MonsterLDir.Append("Bat1_L");

			UImageManager::GetInst().LoadFolder(MonsterLDir.GetPathToString());

			UEngineDirectory MonsterRDir;
			MonsterRDir.MoveParentToDirectory("Resources/Monster_R");
			MonsterRDir.Append("Bat1_R");

			UImageManager::GetInst().LoadFolder(MonsterRDir.GetPathToString());
		}
	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VampireSurvivors");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 800 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AInGameMode, AActor>("InGame");
	UEngineAPICore::GetCore()->CreateLevel<AResultGameMode, AActor>("Result");
	
	UEngineAPICore::GetCore()->OpenLevel("Title");
	//UEngineAPICore::GetCore()->OpenLevel("InGame");
}

void VamSurContentsCore::Tick()
{
}