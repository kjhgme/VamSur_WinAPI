#include "PreCompile.h"
#include "DieUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>

DieUI::DieUI()
{	
	SetActorLocation(UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation());
	
	{
		BackGroundRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackGroundRenderer->SetSprite("TitleBG.png");
		BackGroundRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 10);
		BackGroundRenderer->SetSpriteScale(BackGroundScale);

		GameOverRenderer = CreateDefaultSubObject<USpriteRenderer>();
		GameOverRenderer->SetSprite("GameOver.png");
		GameOverRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 20);
		GameOverRenderer->SetSpriteScale(1.0f);

		BackButtonRenderer = CreateDefaultSubObject<USpriteRenderer>();
		BackButtonRenderer->SetSprite("DieUI_BackButton.png");
		BackButtonRenderer->SetOrder(static_cast<int>(ERenderOrder::UI) + 20);
		BackButtonRenderer->SetSpriteScale(ButtonScale);

		LeftCursorRenderer = CreateDefaultSubObject<USpriteRenderer>();
		LeftCursorRenderer->SetSprite("Cursor", 0);
		LeftCursorRenderer->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
		LeftCursorRenderer->SetSpriteScale(ButtonScale);
		LeftCursorRenderer->CreateAnimation("Cursor_L", "Cursor", 0, 7, 0.15f);
		LeftCursorRenderer->ChangeAnimation("Cursor_L");

		RightCursorRenderer = CreateDefaultSubObject<USpriteRenderer>();
		RightCursorRenderer->SetSprite("Cursor", 8);
		RightCursorRenderer->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
		RightCursorRenderer->SetSpriteScale(ButtonScale);
		RightCursorRenderer->CreateAnimation("Cursor_R", "Cursor", 8, 15, 0.15f);
		RightCursorRenderer->ChangeAnimation("Cursor_R");
	}

	GameOverRenderer->SetAlphafloat(GameOverAlpha);
	BackGroundRenderer->SetAlphafloat(BackGroundAlpha);
	BackButtonRenderer->SetAlphafloat(1.0f);
	LeftCursorRenderer->SetAlphafloat(1.0f);
	RightCursorRenderer->SetAlphafloat(1.0f);

	GameOverRenderer->AddComponentLocation({ 0.0f, -100.0f });
	BackButtonRenderer->AddComponentLocation({ 0.0f, 50.0f });
	LeftCursorRenderer->AddComponentLocation({ -130.0f, 200.0f });
	RightCursorRenderer->AddComponentLocation({ 130.0f, 200.0f });

	TimeEventer.PushEvent(5.0f, std::bind(&DieUI::UIAnimation, this), true, 1.0f, false);
}

DieUI::~DieUI()
{
}

void DieUI::UIAnimation()
{
	float DeltaTime = UEngineAPICore::GetCore()->GetDeltaTime();
	GameOverAlpha += DeltaTime * 2.0f;
	GameOverAlpha = UEngineMath::Clamp(GameOverAlpha, 0.0f, 1.0f);
	GameOverRenderer->SetAlphafloat(GameOverAlpha);
	
	if (0.5f <= GameOverAlpha)
	{
		BackGroundAlpha += DeltaTime * 1.5f;
		BackGroundAlpha = UEngineMath::Clamp(BackGroundAlpha, 0.0f, 0.5f);
		BackGroundRenderer->SetAlphafloat(BackGroundAlpha);

		BackGroundScale -= DeltaTime * 2.0f;
		BackGroundScale = UEngineMath::ClampMin(BackGroundScale, 1.0f);
		BackGroundRenderer->SetSpriteScale(BackGroundScale);
	}

	if (1.0f >= BackGroundScale)
	{
		ButtonScale += DeltaTime * 3.0f;
		ButtonScale = UEngineMath::ClampMax(ButtonScale, 1.0f);
		BackButtonRenderer->SetSpriteScale(ButtonScale);

		LeftCursorRenderer->SetSpriteScale(ButtonScale);
		RightCursorRenderer->SetSpriteScale(ButtonScale);
	}
}
