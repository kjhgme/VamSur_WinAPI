#pragma once
#include <EngineCore/EngineAPICore.h>

class VamSurContentsCore : public UContentsCore
{
public:
	VamSurContentsCore();
	~VamSurContentsCore();

	VamSurContentsCore(const VamSurContentsCore& _Other) = delete;
	VamSurContentsCore(VamSurContentsCore&& _Other) noexcept = delete;
	VamSurContentsCore& operator=(const VamSurContentsCore& _Other) = delete;
	VamSurContentsCore& operator=(VamSurContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick() override;

private:
};

