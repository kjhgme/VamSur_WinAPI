#pragma once
#include <string>

#include "Player.h"

class Antonio : public APlayer
{
public:
	Antonio();
	~Antonio();

	Antonio(const Antonio& _Other) = delete;
	Antonio(Antonio&& _Other) noexcept = delete;
	Antonio& operator=(const Antonio& _Other) = delete;
	Antonio& operator=(Antonio&& _Other) noexcept = delete;

	void InitSprite() override;
	void InitPlayerStatus() override;

protected:

private:
	struct AntonioS
	{
		std::string Name = "Antonio";
		int Health = 120;
		int Armor = 1;
		int Might = 0;
		int Speed = 160;
	} AntonioStatus;
};

