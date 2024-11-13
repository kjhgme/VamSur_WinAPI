#include "PreCompile.h"
#include "Whip.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

Whip::Whip()
{
}

Whip::~Whip()
{
}

void Whip::BeginPlay()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetOrder(ERenderOrder::WEAPON);
	SpriteRenderer->SetSprite("Whip", 0);
	SpriteRenderer->SetComponentLocation({ 110.0f, -10.0f });
	SpriteRenderer->SetSpriteScale(1.0f);

	Level = 1;
}

void Whip::Tick(float _DeltaTime)
{
	AWeapon::Tick(_DeltaTime);
}

void Whip::Action()
{
	FadeOut();
}

void Whip::FadeIn()
{
	FadeValue = 0.0f;
	FadeDir = 1.0f;
	TimeEventer.PushEvent(0.5f, std::bind(&Whip::FadeChange, this), true);
}

void Whip::FadeOut()
{
	FadeValue = 1.0f;
	FadeDir = -1.0f;
	TimeEventer.PushEvent(0.5f, std::bind(&Whip::FadeChange, this), true);
}

void Whip::FadeChange()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	FadeValue += DeltaTime * 2.0f * FadeDir;
	SpriteRenderer->SetAlphafloat(FadeValue);
}
