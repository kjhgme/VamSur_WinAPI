#include "PreCompile.h"
#include "EngineMath.h"

//
const FVector2D FVector2D::ZERO = { 0, 0 };

//
const FVector2D FVector2D::LEFT = { -1, 0 };
const FVector2D FVector2D::RIGHT = { 1, 0 };
const FVector2D FVector2D::UP = { 0, -1 };
const FVector2D FVector2D::DOWN = { 0, 1 };

//
const FIntPoint FIntPoint::LEFT = {-1, 0};
const FIntPoint FIntPoint::RIGHT = { 1, 0 };
const FIntPoint FIntPoint::UP = { 0, -1 };
const FIntPoint FIntPoint::DOWN = { 0, 1 };

// 
const UColor UColor::WHITE = { 255, 255, 255, 0 };
const UColor UColor::BLACK = { 0, 0, 0, 0 };

//
FIntPoint FVector2D::ConvertToPoint() const
{
	return { iX(), iY() };
}

std::function<bool(const FTransform&, const FTransform&)> FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)];

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;

		FTransform::AllCollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CirCleToCirCle;
	}
};

CollisionFunctionInit Inst = CollisionFunctionInit();

bool FTransform::Collision(ECollisionType _LeftType, const FTransform& _Left, ECollisionType _RightType, const FTransform& _Right)
{
	return FTransform::AllCollisionFunction[static_cast<int>(_LeftType)][static_cast<int>(_RightType)](_Left, _Right);
}

bool FTransform::CirCleToCirCle(const FTransform& _Left, const FTransform& _Right)
{
	FVector2D Len = _Left.Location - _Right.Location;

	if (Len.Length() < _Left.Scale.Half().X + _Right.Scale.Half().X)
	{
		return true;
	}

	return false;
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{

	if (_Left.CenterLeftTop().X > _Right.CenterRightBottom().X)
	{
		return false;
	}

	if (_Left.CenterRightBottom().X < _Right.CenterLeftTop().X)
	{
		return false;
	}

	if (_Left.CenterLeftTop().Y > _Right.CenterRightBottom().Y)
	{
		return false;
	}

	if (_Left.CenterRightBottom().Y < _Right.CenterLeftTop().Y)
	{
		return false;
	}

	return true;
}
