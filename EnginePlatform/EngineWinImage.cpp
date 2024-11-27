#include "PreCompile.h"
#include "EngineWinImage.h"

#include <EngineBase/EnginePath.h>
#include <EngineBase/EngineString.h>

// GDI Plus
#include <objidl.h>
#include <gdiplus.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

UEngineWinImage::UEngineWinImage()
{
}

UEngineWinImage::~UEngineWinImage()
{
}

void UEngineWinImage::Create(UEngineWinImage* _TargetImage, FVector2D _Scale)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("Main windowDC is not exist.(UEngineWinImage::Create)");
		return;
	}

	HBITMAP NewBitmap = static_cast<HBITMAP>(CreateCompatibleBitmap(_TargetImage->GetDC(), _Scale.iX(), _Scale.iY()));
	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));

	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}

void UEngineWinImage::CopyToBit(UEngineWinImage* _TargetImage, const FTransform& _Trans)
{
	if (nullptr == _TargetImage)
	{
		MSGASSERT("TargetImage is not exist.(UEngineWinImage::CopyToBit)");
	}

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;

	FVector2D LeftTop = _Trans.CenterLeftTop();
	FVector2D RightBot = _Trans.CenterRightBottom();

	BitBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_Trans.Scale.iX(),
		_Trans.Scale.iY(),
		CopyDC,
		0,
		0,
		SRCCOPY);
}

void UEngineWinImage::CopyToTrans(UEngineWinImage* _TargetImage, const FTransform& _RenderTrans, const FTransform& _LTImageTrans, UColor _Color)
{
	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;

	FVector2D LeftTop = _RenderTrans.CenterLeftTop();

	//_In_ HDC hdcDest,					TargetHDC
	//_In_ int xoriginDest,				PosX
	//_In_ int yoriginDest,				PosY
	//_In_ int wDest,					ScaleX
	//_In_ int hDest,					ScaleY
	//_In_ HDC hdcSrc,					Image
	//_In_ int xoriginSrc,				ImagePosX
	//_In_ int yoriginSrc,				ImagePosY
	//_In_ int wSrc,					ImageScaleX
	//_In_ int hSrc,					ImageScaleY
	//_In_ UINT crTransparent			Color

	TransparentBlt(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_RenderTrans.Scale.iX(),
		_RenderTrans.Scale.iY(),
		CopyDC,
		_LTImageTrans.Location.iX(),
		_LTImageTrans.Location.iY(),
		_LTImageTrans.Scale.iX(),
		_LTImageTrans.Scale.iY(),
		_Color.Color
	);
}

void UEngineWinImage::CopyToAlpha(UEngineWinImage* _TargetImage,
	const FTransform& _RenderTrans,
	const FTransform& _LTImageTrans,
	unsigned char _Alpha)
{
	BLENDFUNCTION BLEND;
	BLEND.BlendOp = AC_SRC_OVER;
	BLEND.BlendFlags = 0;
	BLEND.AlphaFormat = AC_SRC_ALPHA;
	BLEND.SourceConstantAlpha = _Alpha;

	HDC CopyDC = ImageDC;
	HDC TargetDC = _TargetImage->ImageDC;
	FVector2D LeftTop = _RenderTrans.CenterLeftTop();

	AlphaBlend(
		TargetDC,
		LeftTop.iX(),
		LeftTop.iY(),
		_RenderTrans.Scale.iX(),
		_RenderTrans.Scale.iY(),
		CopyDC,
		_LTImageTrans.Location.iX(),
		_LTImageTrans.Location.iY(),
		_LTImageTrans.Scale.iX(),
		_LTImageTrans.Scale.iY(),
		BLEND
	);
}

void UEngineWinImage::Load(UEngineWinImage* _TargetImage, std::string_view _Path)
{
	UEnginePath Path = _Path;

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

	HBITMAP NewBitmap = nullptr;

	if (".PNG" == UpperExt)
	{
		ULONG_PTR gdiplustoken = 0;

		Gdiplus::GdiplusStartupInput StartupInput;
		Gdiplus::GdiplusStartup(&gdiplustoken, &StartupInput, nullptr);

		std::wstring WidePath = UEngineString::AnsiToUnicode(_Path);

		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(WidePath.c_str());

		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());

		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(255, 255, 0, 255), &NewBitmap);

		if (Gdiplus::Status::Ok != stat)
		{
			MSGASSERT("PNG load fail.(UEngineWinImage::Load)" + std::string(_Path));
			return;
		}

		delete pBitMap;
		delete pImage;
	}

	if (nullptr == NewBitmap)
	{
		MSGASSERT("image load fail.(UEngineWinImage::Load)");
		return;
	}

	HDC NewImageDC = CreateCompatibleDC(_TargetImage->GetDC());

	HBITMAP OldBitMap = static_cast<HBITMAP>(SelectObject(NewImageDC, NewBitmap));
	DeleteObject(OldBitMap);

	hBitMap = NewBitmap;
	ImageDC = NewImageDC;

	GetObject(hBitMap, sizeof(BITMAP), &Info);
}
