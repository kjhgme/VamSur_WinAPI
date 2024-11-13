#include "PreCompile.h"
#include "Whip.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

Whip::Whip()
{
}

Whip::~Whip()
{
}

void Whip::BeginPlay()
{
	{
		IconSpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		IconSpriteRenderer->SetOrder(ERenderOrder::UI);
		IconSpriteRenderer->SetSprite("WeaponIcon", 0);
		IconSpriteRenderer->SetComponentLocation({ -620.0f, -350.0f });
		IconSpriteRenderer->SetSpriteScale(1.0f);
	}

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::WEAPON);
		SpriteRenderer->SetSprite("Whip", 0);
		SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetAlphaChar(0);
	}

	Level = 1;
}

void Whip::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);	

	if (0.9f <= FadeValue)
	{
		Active = true;
	}
	else {
		Active = false;
	}
}

void Whip::Action()
{
	TimeEventer.PushEvent(2.0f, std::bind(&Whip::Attack, this), false, -1.0f, true);
}

void Whip::ChangeHeadDir()
{
	AWeapon::ChangeHeadDir();
	
	if (true == Active || 0 >= FadeValue)
	{
		if (true == HeadDirRight)
		{
			SpriteRenderer->SetSprite("Whip", 0);
			SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });
		}
		else
		{
			SpriteRenderer->SetSprite("Whip", 1);
			SpriteRenderer->SetComponentLocation({ -110.0f, -10.0f });
		}
	}
}

void Whip::Attack()
{
	FadeValue = 1.0f;
	TimeEventer.PushEvent(0.5f, std::bind(&Whip::FadeOut, this), true);
}

void Whip::FadeOut()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 2.0f * FadeDir;
	SpriteRenderer->SetAlphafloat(FadeValue);
}
