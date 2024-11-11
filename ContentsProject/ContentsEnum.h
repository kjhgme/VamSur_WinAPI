#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	PLAYER = 0,
	UI = 1000,
	CURSOR = 10000,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
	WeaponBody,
	ObjectBody,
	ItemBody
};
