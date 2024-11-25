#include "PreCompile.h"
#include "VamSurContentsCore.h"

#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineFile.h>
#include <EnginePlatform/EngineSound.h>
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
			{
				UEngineDirectory UIDir;
				if (false == UIDir.MoveParentToDirectory("Resources/InGame/InGameUI"))
				{
					MSGASSERT("Resources folder is not exist.(VamSurContentsCore::BeginPlay)");
					return;
				}

				std::vector<UEngineFile> ImageFiles = UIDir.GetAllFile();

				for (size_t i = 0; i < ImageFiles.size(); i++)
				{
					std::string FilePath = ImageFiles[i].GetPathToString();
					UImageManager::GetInst().Load(FilePath);
				}
			}
			{
				UEngineDirectory CursorDir;
				CursorDir.MoveParentToDirectory("Resources/UI");
				CursorDir.Append("Cursor");

				UImageManager::GetInst().LoadFolder(CursorDir.GetPathToString());
			}

			{
				UEngineDirectory Dir;
				Dir.MoveParentToDirectory("Resources/UI/Letter");
				Dir.Append("Letters");

				UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
			} 
			{
				UEngineDirectory Dir;
				Dir.MoveParentToDirectory("Resources/UI/Letter");
				Dir.Append("DamageNum");

				UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
			}
		}
		// Item
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("Resources/Item"))
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

			{
				UEngineDirectory Dir;
				Dir.MoveParentToDirectory("Resources/InGame");
				Dir.Append("ItemContainer");
				UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
			}
		}
		// Characters
		{
			LoadCharacterImages("Antonio");
			LoadCharacterImages("Imelda");
		}
		// Blood
		{
			UEngineDirectory Dir;
			Dir.MoveParentToDirectory("Resources");
			Dir.Append("Blood");

			UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
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
			LoadMonsterImages("Bat1");
			LoadMonsterImages("Ghoul1");
		}
		// Weapon
		{
			LoadWeaponImages("WeaponIcon");
			LoadWeaponImages("Whip");
			LoadWeaponImages("MagicWand");
			LoadWeaponImages("Knife");
		}
		// Sounds
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("Resources"))
			{
				MSGASSERT("Resources folder is not exist.(VamSurContentsCore::BeginPlay)");
				return;
			}
			Dir.Append("Sounds");

			std::vector<UEngineFile> SoundFiles = Dir.GetAllFile();

			for (size_t i = 0; i < SoundFiles.size(); i++)
			{
				std::string FilePath = SoundFiles[i].GetPathToString();
				UEngineSound::Load(FilePath);
			}
		}
	}

	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("VampireSurvivors");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 800 });

	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->CreateLevel<AInGameMode, AActor>("InGame");
	UEngineAPICore::GetCore()->CreateLevel<AResultGameMode, AActor>("Result");
	
	//UEngineAPICore::GetCore()->OpenLevel("Title");
	UEngineAPICore::GetCore()->OpenLevel("InGame");
}

void VamSurContentsCore::Tick()
{
}

void VamSurContentsCore::LoadCharacterImages(const std::string_view characterName)
{
	UEngineDirectory CharacterDir;
	CharacterDir.MoveParentToDirectory("Resources/Characters");
	CharacterDir.Append(characterName);
	UImageManager::GetInst().LoadFolder(CharacterDir.GetPathToString());
}

void VamSurContentsCore::LoadMonsterImages(const std::string& monsterName)
{
	// Left direction images
	UEngineDirectory MonsterLDir;
	MonsterLDir.MoveParentToDirectory("Resources/Monster_L");
	MonsterLDir.Append(monsterName + "_L");
	UImageManager::GetInst().LoadFolder(MonsterLDir.GetPathToString());

	// Right direction images
	UEngineDirectory MonsterRDir;
	MonsterRDir.MoveParentToDirectory("Resources/Monster_R");
	MonsterRDir.Append(monsterName + "_R");
	UImageManager::GetInst().LoadFolder(MonsterRDir.GetPathToString());
}

void VamSurContentsCore::LoadWeaponImages(const std::string_view weaponName)
{
	UEngineDirectory WeaponDir;
	WeaponDir.MoveParentToDirectory("Resources/Weapon");
	WeaponDir.Append(weaponName);
	UImageManager::GetInst().LoadFolder(WeaponDir.GetPathToString());
}
