#include "PreCompile.h"
#include "TitleBG.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWindow.h>

#include "ContentsEnum.h"

ATitleBG::ATitleBG()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.X / 2, WindowSize.Y / 2 });

	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("TitleBG.png");
	SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
	SpriteRenderer->SetSpriteScale(1.0f);
}

ATitleBG::~ATitleBG()
{
}
