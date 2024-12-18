﻿#pragma once
#include <string>
#include <map>

#include <EnginePlatform/EngineWinImage.h>

#include "EngineSprite.h"

class UImageManager
{
public:
	~UImageManager();

	UImageManager(const UImageManager& _Other) = delete;
	UImageManager(UImageManager&& _Other) noexcept = delete;
	UImageManager& operator=(const UImageManager& _Other) = delete;
	UImageManager& operator=(UImageManager&& _Other) noexcept = delete;

	static UImageManager& GetInst()
	{
		static UImageManager Inst;
		return Inst;
	}

	void Load(std::string_view _Path);
	void Load(std::string_view _KeyName, std::string_view _Path);

	void LoadFolder(std::string_view _Path);
	void LoadFolder(std::string_view _KeyName, std::string_view _Path);

	bool IsLoadSprite(std::string_view _KeyName);

	UEngineSprite* FindSprite(std::string_view _KeyName);
	UEngineWinImage* FindImage(std::string_view _KeyName);

protected:

private:
	UImageManager();

	std::map<std::string, UEngineWinImage*> Images;
	std::map<std::string, UEngineSprite*> Sprites;
};

