﻿#pragma once
class ATitleLogo : public AActor
{
public:
	ATitleLogo();
	~ATitleLogo();

	ATitleLogo(const ATitleLogo& _Other) = delete;
	ATitleLogo(ATitleLogo&& _Other) noexcept = delete;
	ATitleLogo& operator=(const ATitleLogo& _Other) = delete;
	ATitleLogo& operator=(ATitleLogo&& _Other) noexcept = delete;

	void Opening();

protected:

private:
	class USpriteRenderer* SpriteRenderer = nullptr;
};

