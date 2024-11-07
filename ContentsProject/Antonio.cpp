#include "PreCompile.h"
#include "Antonio.h"

Antonio::Antonio()
{
}

Antonio::~Antonio()
{
}

void Antonio::InitSprite()
{
	SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
	SpriteRenderer->SetSprite("Antonio", 4);
	SpriteRenderer->SetComponentScale({ 68, 68 });
}

void Antonio::InitPlayerStatus()
{
	PlayerStatus.Name		= AntonioStatus.Name;
	PlayerStatus.Health		= AntonioStatus.Health;
	PlayerStatus.Armor		= AntonioStatus.Armor;
	PlayerStatus.Might		= AntonioStatus.Might;
	PlayerStatus.Speed		= AntonioStatus.Speed;
}
