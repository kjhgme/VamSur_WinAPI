﻿#pragma once

#include <string.h>

#include "MonsterStatus.h"

class AMonster : public AActor
{
public:
	AMonster();
	~AMonster();

	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void InitMonster(MonsterStatus _Type);
	void InitMonsterStatus(MonsterStatus _Type);
	void InitSprite();
	void InitCreateMonAnim();
	void InitCollision();

	// GetFunction
	float GetAttPower()
	{
		return Status.AttPower;
	}

	FVector2D GetMonsterSize()
	{
		return SpriteRenderer->GetComponentScale();
	}

	// SetFunction
	void SetMonsterPos(FVector2D _pos);
	void SetHp(float _Hp)
	{
		Status.Hp = _Hp;
	}
	
	void SetChest(bool _Has)
	{
		bHasChest = _Has;
	}

	void SetMapEvent(bool _Has)
	{
		bMapEvent = _Has;
	}

	// Function
	void ChasePlayer(float _DeltaTime);
	void ChangeAnimation();
	void Die();
	void TakeDamage(float _Att, float _KnockBack);
	void EnableCollision();

	void CollisionStay(AActor* _ColActor);

	void SpawnExpItem();
	void KnockbackEnd();

	class U2DCollision* CollisionComponent = nullptr;

protected:
	MonsterStatus Status;
	
	class USpriteRenderer* SpriteRenderer = nullptr;

private:
	bool HeadDirRight = false;
	bool Alive = true;
	bool Hitable = true;
	bool bHasChest = false;
	bool bMapEvent = false;
	bool bSpawnExp = true;
	int count = 0;

	float KnockbackAmount = 0.0f;

	FVector2D MonsterPos{};
	FVector2D PlayerPos{};
	FVector2D FirstDiffPos{};
	FVector2D DiffPos{};
	FVector2D KnockBack{};

	class ATextBox* DamageText = nullptr;
	float TextFadeValue = 1.0f;
	float TextFadeDir = -1.0f;

	void TextFadeOut();
};

