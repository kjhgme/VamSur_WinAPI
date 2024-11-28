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
			{
				UEngineDirectory Dir;
				if (false == Dir.MoveParentToDirectory("Resources/Item/Items"))
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
			}
			{
				LoadItemImages("Chest");
				LoadItemImages("ChestCursor");
				LoadItemImages("Orologion");
				LoadItemImages("Rosary");
				LoadItemImages("Tanto");
				LoadItemImages("Vacuum");
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
			LoadMonsterImages("Bat2");
			LoadMonsterImages("Bat3");
			LoadMonsterImages("Bat4");
			LoadMonsterImages("Bat5");
			LoadMonsterImages("Bat6");
			LoadMonsterImages("Flower1");
			LoadMonsterImages("Flower2");
			LoadMonsterImages("Ghost");
			LoadMonsterImages("Ghoul1");
			LoadMonsterImages("Ghoul2");
			LoadMonsterImages("Ghoul3");
			LoadMonsterImages("Mudman1");
			LoadMonsterImages("Mudman2");
			LoadMonsterImages("Mummy");
			LoadMonsterImages("Skeleton1");
			LoadMonsterImages("Skeleton2");
			LoadMonsterImages("Skeleton3");
			LoadMonsterImages("Skeleton4");
			LoadMonsterImages("Skeleton5");
			LoadMonsterImages("Skeleton6");
			LoadMonsterImages("Werewolf1");
			LoadMonsterImages("XLBat");
			LoadMonsterImages("XLFlower1");
			LoadMonsterImages("XLMantis");
			LoadMonsterImages("XLMedusa");
			LoadMonsterImages("XLMummy");
			LoadMonsterImages("XLReaper");
		}
		// Weapon
		{
			LoadWeaponImages("WeaponIcon");
			LoadWeaponImages("Whip");
			LoadWeaponImages("MagicWand");
			LoadWeaponImages("Knife");
			LoadWeaponImages("KingBible");
			LoadWeaponImages("Garlic");
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
	
	UEngineAPICore::GetCore()->OpenLevel("Title");
	//UEngineAPICore::GetCore()->OpenLevel("InGame");
}

void VamSurContentsCore::Tick()
{
}

void VamSurContentsCore::LoadItemImages(const std::string_view _ItemName)
{
	UEngineDirectory ItemDir;
	ItemDir.MoveParentToDirectory("Resources/Item");
	ItemDir.Append(_ItemName);
	UImageManager::GetInst().LoadFolder(ItemDir.GetPathToString());
}

void VamSurContentsCore::LoadCharacterImages(const std::string_view _CharacterName)
{
	UEngineDirectory CharacterDir;
	CharacterDir.MoveParentToDirectory("Resources/Characters");
	CharacterDir.Append(_CharacterName);
	UImageManager::GetInst().LoadFolder(CharacterDir.GetPathToString());
}

void VamSurContentsCore::LoadMonsterImages(const std::string& _MonsterName)
{
	// Left direction images
	UEngineDirectory MonsterLDir;
	MonsterLDir.MoveParentToDirectory("Resources/Monster_L");
	MonsterLDir.Append(_MonsterName + "_L");
	UImageManager::GetInst().LoadFolder(MonsterLDir.GetPathToString());

	// Right direction images
	UEngineDirectory MonsterRDir;
	MonsterRDir.MoveParentToDirectory("Resources/Monster_R");
	MonsterRDir.Append(_MonsterName + "_R");
	UImageManager::GetInst().LoadFolder(MonsterRDir.GetPathToString());
}

void VamSurContentsCore::LoadWeaponImages(const std::string_view _WeaponName)
{
	UEngineDirectory WeaponDir;
	WeaponDir.MoveParentToDirectory("Resources/Weapon");
	WeaponDir.Append(_WeaponName);
	UImageManager::GetInst().LoadFolder(WeaponDir.GetPathToString());
}
