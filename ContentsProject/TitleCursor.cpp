#include "PreCompile.h"
#include "TitleCursor.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>

#include "ContentsEnum.h"

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
		LeftCursor->SetOrder(static_cast<int>(ERenderOrder::UI));
		LeftCursor->SetSpriteScale(1.0f);

		LeftCursor->CreateAnimation("Cursor_L", "Cursor", 0, 7, 0.15f);
		LeftCursor->ChangeAnimation("Cursor_L");
	}
	{
		RightCursor = CreateDefaultSubObject<USpriteRenderer>();
		RightCursor->SetSprite("Cursor", 8);
		RightCursor->SetOrder(static_cast<int>(ERenderOrder::UI));
		RightCursor->SetSpriteScale(1.0f);

		RightCursor->CreateAnimation("Cursor_R", "Cursor", 8, 15, 0.15f);
		RightCursor->ChangeAnimation("Cursor_R");

		UpdateCursorPosition();
	}
}

void ATitleCursor::Tick(float _DeltaTime)
{
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
		if(START == pos.GetPosID())
		UEngineAPICore::GetCore()->OpenLevel("InGame");
	}

	UpdateCursorPosition();
}

void ATitleCursor::UpdateCursorPosition()
{
	CPos currentPos = pos.GetPos();
	LeftCursor->SetComponentLocation(currentPos.LCP);
	RightCursor->SetComponentLocation(currentPos.RCP);
}