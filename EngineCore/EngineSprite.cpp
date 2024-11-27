#include "PreCompile.h"
#include "EngineSprite.h"

#include <EngineBase/EngineDebug.h>

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}


void UEngineSprite::PushData(UEngineWinImage* _Image, const FTransform& _Trans)
{
	if (true == _Trans.Scale.IsZeroed())
	{
		MSGASSERT("Sprite's scale is 0.(UEngineSprite::PushData)");
	}


	// 리스트 이니셜라이저
	Data.push_back({ _Image, _Trans });
}


