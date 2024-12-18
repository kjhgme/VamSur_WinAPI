﻿#include "PreCompile.h"
#include "RosaryItem.h"
#include "ContentsEnum.h"

#include "InGameMode.h"

ARosaryItem::ARosaryItem()
{
	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Rosary", 0);
		SpriteRenderer->SetSpriteScale(1.0f);
		SpriteRenderer->SetOrder(ERenderOrder::ITEM);
		SpriteRenderer->CreateAnimation("RosaryAnim", "Rosary", 0, 2, 0.1f);
		SpriteRenderer->ChangeAnimation("RosaryAnim");
	}
}

ARosaryItem::~ARosaryItem()
{
}

void ARosaryItem::ApplyItemEffect()
{
	ADropItem::ApplyItemEffect();

	auto& SpawnedMonsters = AInGameMode::MonsterSpawner->SpawnedMonsters;

	for (auto it = SpawnedMonsters.begin(); it != SpawnedMonsters.end();) {
		auto* Monster = *it;

		Monster->Die();

		it = SpawnedMonsters.begin();
	}

	GetSoundPlayer = UEngineSound::Play("sfx_autoLevel.wav");
}
