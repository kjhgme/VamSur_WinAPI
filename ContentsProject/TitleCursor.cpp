#include "PreCompile.h"
#include "TitleCursor.h"

#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
// #include <EnginePlatform/EngineWindow.h>

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
		LeftCursor->SetComponentLocation(pos.GetPos().LCP);

		LeftCursor->CreateAnimation("Cursor_L", "Cursor", 0, 7, 0.15f);
		LeftCursor->ChangeAnimation("Cursor_L");
	}
	{
		RightCursor = CreateDefaultSubObject<USpriteRenderer>();
		RightCursor->SetSprite("Cursor", 8);
		RightCursor->SetOrder(static_cast<int>(ERenderOrder::UI));
		RightCursor->SetSpriteScale(1.0f);
		RightCursor->SetComponentLocation(pos.GetPos().LCP);

		RightCursor->CreateAnimation("Cursor_R", "Cursor", 8, 15, 0.15f);
		RightCursor->ChangeAnimation("Cursor_R");
	}
}

void ATitleCursor::Tick(float _DeltaTime)
{
	if (true == UEngineInput::GetInst().IsDown('D'))
	{
		pos.move("right");
		LeftCursor->SetComponentLocation(pos.GetPos().LCP);
		RightCursor->SetComponentLocation(pos.GetPos().RCP);
	}
	else if (true == UEngineInput::GetInst().IsDown('A'))
	{
		pos.move("left");
		LeftCursor->SetComponentLocation(pos.GetPos().LCP);
		RightCursor->SetComponentLocation(pos.GetPos().RCP);
	}
	else if (true == UEngineInput::GetInst().IsDown('S'))
	{
		pos.move("down");
		LeftCursor->SetComponentLocation(pos.GetPos().LCP);
		RightCursor->SetComponentLocation(pos.GetPos().RCP);
	}
	else if (true == UEngineInput::GetInst().IsDown('W'))
	{
		pos.move("up");
		LeftCursor->SetComponentLocation(pos.GetPos().LCP);
		RightCursor->SetComponentLocation(pos.GetPos().RCP);
	}
}
