#include "PreCompile.h"
#include "TitleCursor.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineSound.h>

#include "ContentsEnum.h"
#include "TitleSelectCharacter.h"

ATitleCursor::ATitleCursor()
{
}

ATitleCursor::~ATitleCursor()
{
}

void ATitleCursor::BeginPlay()
{
	FVector2D WindowSize = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	SetActorLocation({ WindowSize.Half() });

	{
		LeftCursor = CreateDefaultSubObject<USpriteRenderer>();
		LeftCursor->SetSprite("Cursor", 0);
		LeftCursor->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
		LeftCursor->SetSpriteScale(1.0f);
		LeftCursor->SetAlphafloat(0.0f);

		LeftCursor->CreateAnimation("Cursor_L", "Cursor", 0, 7, 0.15f);
		LeftCursor->ChangeAnimation("Cursor_L");
	}
	{
		RightCursor = CreateDefaultSubObject<USpriteRenderer>();
		RightCursor->SetSprite("Cursor", 8);
		RightCursor->SetOrder(static_cast<int>(ERenderOrder::CURSOR));
		RightCursor->SetSpriteScale(1.0f);
		RightCursor->SetAlphafloat(0.0f);

		RightCursor->CreateAnimation("Cursor_R", "Cursor", 8, 15, 0.15f);
		RightCursor->ChangeAnimation("Cursor_R");
	}

	UpdateCursorPosition();
}

void ATitleCursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == Alive)
	{
		UpdateCursorPosition();

		if (true == UEngineInput::GetInst().IsDown('D'))
		{
			pos.move("right");
		}
		else if (true == UEngineInput::GetInst().IsDown('A'))
		{
			pos.move("left");
		}
		else if (true == UEngineInput::GetInst().IsDown('S'))
		{
			pos.move("down");
		}
		else if (true == UEngineInput::GetInst().IsDown('W'))
		{
			pos.move("up");
		}
		else if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
		{
			USoundPlayer ClickSoundPlayer = UEngineSound::Play("sfx_pause_in.wav");

			if (START == pos.GetPosID())
			{
				Alive = false;
				LeftCursor->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND)- 1);
				RightCursor->SetOrder(static_cast<int>(ERenderOrder::BACKGROUND) - 1);
				ATitleSelectCharacter* SelectCharacter = GetWorld()->SpawnActor<ATitleSelectCharacter>();	
			}
			else if (BACK == pos.GetPosID())
			{
				HWND hWnd = UEngineAPICore::GetCore()->GetMainWindow().GetHandle();

				if (hWnd)
				{
					SendMessageA(hWnd, WM_CLOSE, 0, 0);
				}
			}
		}
	}
}

void ATitleCursor::UpdateCursorPosition()
{
	CPos currentPos = pos.GetPos();
	LeftCursor->SetComponentLocation(currentPos.LCP);
	RightCursor->SetComponentLocation(currentPos.RCP);
}
