#pragma once
#include <EngineCore/EngineAPICore.h>

class VamSurContentsCore : public UContentsCore
{
public:
	VamSurContentsCore();
	~VamSurContentsCore();

	VamSurContentsCore(const VamSurContentsCore& _Other) = delete;
	VamSurContentsCore(VamSurContentsCore&& _Other) noexcept = delete;
	VamSurContentsCore& operator=(const VamSurContentsCore& _Other) = delete;
	VamSurContentsCore& operator=(VamSurContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
	ULevel* TitleLevel = nullptr;
	ULevel* InGameLevel = nullptr;
	ULevel* ResultLevel = nullptr;

	void LoadItemImages(const std::string_view _ItemName);
	void LoadCharacterImages(const std::string_view _CharacterName);
	void LoadMonsterImages(const std::string& _MonsterName);
	void LoadWeaponImages(const std::string_view _WeaponName);
};

