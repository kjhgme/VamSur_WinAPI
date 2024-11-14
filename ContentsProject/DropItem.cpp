#include "PreCompile.h"
#include "DropItem.h"
#include "ContentsEnum.h"

ADropItem::ADropItem()
{
}

ADropItem::~ADropItem()
{
}

void ADropItem::SetLocation(FVector2D _Pos)
{
	Pos = _Pos;
	SetActorLocation(Pos);
}
