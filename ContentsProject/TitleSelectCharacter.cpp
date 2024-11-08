#include "PreCompile.h"
#include "TitleSelectCharacter.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

#include "ContentsEnum.h"
#include "Player.h"

ATitleSelectCharacter::ATitleSelectCharacter()
{
	Characters.resize(2);
}

ATitleSelectCharacter::~ATitleSelectCharacter()
{
}

void ATitleSelectCharacter::BeginPlay()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.Half() });

	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("TitleUI_SelectCharacterPanel.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("TitleUI_CharacterPanel.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("TitleUI_CharDescPanel.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("TitleUI_CharacterSelectButton.png");
		SpriteRenderer->SetOrder(static_cast<int>(ERenderOrder::UI));
		SpriteRenderer->SetSpriteScale(1.0f);
	}
}

void ATitleSelectCharacter::Tick(float _DeltaTime)
{
}