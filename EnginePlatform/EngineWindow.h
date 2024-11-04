#pragma once
#include "PreCompile.h"
#include <Windows.h>

#include <EngineBase/EngineDelegate.h>

#include "EngineWinImage.h"

class UEngineWindow
{
public:
	static void EngineWindowInit(HINSTANCE _Instance);
	static void CreateWindowClass(const WNDCLASSEXA& _Class);
	static bool IsWindowClass(const std::string_view _Text);
	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	UEngineWindow();
	~UEngineWindow();

	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");
	void Open(std::string_view _TitleName = "Window");
	
	// GetFunction
	inline FVector2D GetWindowSize() const
	{
		return WindowSize;
	}

	inline UEngineWinImage* GetBackBuffer() const
	{
		return BackBufferImage;
	}

	inline UEngineWinImage* GetWindowImage() const
	{
		return WindowImage;
	}

	FVector2D GetMousePos();

	// SetFunction
	inline void SetWindowTitle(std::string_view Text)
	{
		SetWindowTextA(WindowHandle, Text.data());
	}

	void SetWindowPosAndScale(FVector2D _Pos, FVector2D _Scale);

protected:

private:
	static HINSTANCE hInstance;
	static std::map<std::string, WNDCLASSEXA> WindowClasss;

	FVector2D WindowSize;

	HWND WindowHandle = nullptr;
	UEngineWinImage* BackBufferImage = nullptr;
	UEngineWinImage* WindowImage = nullptr;
};

