﻿#pragma once
#include <EngineBase/EngineResources.h>
#include <map>

#include "ThirdParty/FMOD/inc/fmod.hpp"

class USoundPlayer
{
public:
	friend class UEngineSound;

	void On()
	{
		Control->setPaused(false);
	}

	void Off()
	{
		Control->setPaused(true);
	}

	void OnOffSwtich()
	{
		bool Check = false;
		Control->getPaused(&Check);

		if (true == Check)
		{
			Control->setPaused(false);
		}
		else
		{
			Control->setPaused(true);
		}
	}

	void Stop()
	{
		Control->stop();
		Control = nullptr;
	}

	bool IsPlaying()
	{
		bool Check = true;
		Control->isPlaying(&Check);
		return Check;
	}

	void Loop(int Count = -1)
	{
		Control->setLoopCount(Count);
	}

private:
	FMOD::Channel* Control = nullptr;
	FMOD::Sound* SoundHandle = nullptr;
};

class UEngineSound : public UEngineResources
{
public:
	UEngineSound();
	~UEngineSound();

	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view _Path);
	static void Load(std::string_view _Name, std::string_view _Path);
	static USoundPlayer Play(std::string_view _Name);
	static UEngineSound* Find(std::string_view _Name);
	static void Release();

	static void Update();

	static void AllSoundStop();

protected:

private:
	static std::map<std::string, UEngineSound*> Sounds;
	static std::list<USoundPlayer> Players;

	FMOD::Sound* SoundHandle;

	bool ResLoad(std::string_view _Path);
};

