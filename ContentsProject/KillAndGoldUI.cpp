#include "PreCompile.h"
#include "KillAndGoldUI.h"
#include "ContentsEnum.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>

KillAndGoldUI::KillAndGoldUI()
{
	WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetPos();

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("InGameUI_KillAndGold.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}
}

KillAndGoldUI::~KillAndGoldUI()
{
}


void KillAndGoldUI::BeginPlay()
{
}

void KillAndGoldUI::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	SetPos();
}

void KillAndGoldUI::SetPos()
{
	Pos = UEngineAPICore::GetCore()->GetCurLevel()->GetMainPawn()->GetActorLocation();

	SetActorLocation({ Pos });
}
