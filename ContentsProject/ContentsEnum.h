#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	ITEM = -3,
	MONSTER = -2,
	ITEMCONTAINER = -1,
	PLAYER = 0,
	WEAPON = 1,
	UI = 1000,
	CURSOR = 10000,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
	WeaponBody,
	ItemContainerBody,
	DropItemBody
};
