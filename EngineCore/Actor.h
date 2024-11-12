#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/TimeEvent.h>
#include <EngineBase/Object.h>

#include "EngineSprite.h"

class AActor : public UObject
{
public:
	typedef AActor Super;

	friend class ULevel;

	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	virtual void BeginPlay() {}
	virtual void Tick(float _DeltaTime);

	// GetFunction
	class ULevel* GetWorld()
	{
		return World;
	}

	FVector2D GetActorLocation()
	{
		return Transform.Location;
	}

	FTransform GetTransform()
	{
		return Transform;
	}

	// SetFunction
	void SetActorLocation(FVector2D _Location)
	{
		Transform.Location = _Location;
	}

	void SetActorScale(FVector2D _Scale)
	{
		Transform.Scale = _Scale;
	}
	
	// Function
	void AddActorLocation(FVector2D _Direction)
	{
		Transform.Location += _Direction;
	}

	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject()
	{
		ComponentType* NewComponent = new ComponentType();

		UActorComponent* ComponentPtr = dynamic_cast<UActorComponent*>(NewComponent);
		
		ComponentPtr->ParentActor = this;

		Components.push_back(NewComponent);

		ComponentList.push_back(NewComponent);
		return NewComponent;
	}

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

protected:
	UTimeEvent TimeEventer;

private:
	FTransform Transform;

	class ULevel* World = nullptr;

	std::list<class UActorComponent*> Components;
	static std::list<class UActorComponent*> ComponentList;

	static void ComponentBeginPlay();
	void ReleaseCheck(float _DeltaTime) override;
	void ReleaseTimeCheck(float _DeltaTime) override;
};

