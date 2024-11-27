#include "PreCompile.h"
#include "Actor.h"

#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "EngineCoreDebug.h"
#include "ActorComponent.h"
#include "EngineSprite.h"
#include "ImageManager.h"

std::list<UActorComponent*> AActor::ComponentList;

AActor::AActor()
{
}

AActor::~AActor()
{
	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		UActorComponent* Component = *StartIter;

		if (nullptr != Component)
		{
			delete Component;
		}
	}

	Components.clear();
}

void AActor::Tick(float _DeltaTime)
{
	if (true == IsDebug())
	{
		FVector2D Pos = GetActorLocation();
		FVector2D CameraPos = GetWorld()->GetCameraPos();

		FTransform Trans;
		Trans.Location = Pos - CameraPos;
		Trans.Scale = { 6, 6 };

		UEngineDebug::CoreDebugRender(Trans, UEngineDebug::EDebugPosType::Circle);
	}

	TimeEventer.Update(_DeltaTime);

	std::list<class UActorComponent*>::iterator StartIter = Components.begin();
	std::list<class UActorComponent*>::iterator EndIter = Components.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->ComponentTick(_DeltaTime);
	}
}

// private
void AActor::ComponentBeginPlay()
{
	{
		std::list<UActorComponent*>::iterator StartIter = ComponentList.begin();
		std::list<UActorComponent*>::iterator EndIter = ComponentList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			UActorComponent* CurActor = *StartIter;
			CurActor->BeginPlay();
		}

		ComponentList.clear();
	}
}

void AActor::ReleaseCheck(float _DeltaTime)
{
	UObject::ReleaseCheck(_DeltaTime);

	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; )
	{
		UActorComponent* Component = *StartIter;

		if (false == Component->IsDestroy())
		{
			Component->ReleaseCheck(_DeltaTime);
			++StartIter;
			continue;
		}

		delete Component;
		StartIter = Components.erase(StartIter);
	}
}

void AActor::ReleaseTimeCheck(float _DeltaTime)
{
	UObject::ReleaseTimeCheck(_DeltaTime);

	std::list<UActorComponent*>::iterator StartIter = Components.begin();
	std::list<UActorComponent*>::iterator EndIter = Components.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		UActorComponent* Component = *StartIter;
		Component->ReleaseTimeCheck(_DeltaTime);
	}
}
