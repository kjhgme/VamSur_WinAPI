#include "PreCompile.h"
#include "VamSurContentsCore.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include "TitleGameMode.h"
#include "InGameMode.h"
#include "Player.h"

VamSurContentsCore::VamSurContentsCore()
{
}

VamSurContentsCore::~VamSurContentsCore()
{
}

void VamSurContentsCore::BeginPlay()
{
	UEngineDirectory Dir;

	if (false == Dir.MoveParentToDirectory("Resources"))
	{
		MSGASSERT("Resources folder is not exist.(VamSurContentsCore::BeginPlay)");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	{	// Charcters
		UEngineDirectory CharacterDir;
		CharacterDir.MoveParentToDirectory("Resources/Characters");
		CharacterDir.Append("Antonio");

		UImageManager::GetInst().LoadFolder(CharacterDir.GetPathToString());
	}

	{	// Stage
		UEngineDirectory StageDir;
		StageDir.MoveParentToDirectory("Resources");
		StageDir.Append("Stage");

		UImageManager::GetInst().LoadFolder(StageDir.GetPathToString());
	}

	{	// Monster
		UEngineDirectory MonsterLDir;
		MonsterLDir.MoveParentToDirectory("Resources/Monster_L");
		MonsterLDir.Append("Bat1_L");

		UImageManager::GetInst().LoadFolder(MonsterLDir.GetPathToString());

		/*UEngineDirectory MonsterRDir;
		MonsterRDir.MoveParentToDirectory("Resources/Monster_R");
		MonsterRDir.Append("Bat1_R");

		UImageManager::GetInst().LoadFolder(MonsterRDir.GetPathToString());*/
	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VampireSurvivors");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 800 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AInGameMode, APlayer>("InGame");
	UEngineAPICore::GetCore()->CreateLevel<AInGameMode, AActor>("Result");
	
	//UEngineAPICore::GetCore()->OpenLevel("Title");
	UEngineAPICore::GetCore()->OpenLevel("InGame");
}

void VamSurContentsCore::Tick()
{
}