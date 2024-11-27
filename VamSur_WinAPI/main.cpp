#include "PreCompile.h"
#include<EngineCore/EngineAPICore.h>
#include<ContentsProject/VamSurContentsCore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	VamSurContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}