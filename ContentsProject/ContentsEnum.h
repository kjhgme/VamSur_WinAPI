#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	MONSTER = -1,
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
	ObjectBody,
	DropItemBody
};
