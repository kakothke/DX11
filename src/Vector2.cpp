#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Vector2::Vector2()
	: x(0)
	, y(0)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param xy
Vector2::Vector2(float xy)
	: x(xy)
	, y(xy)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param x 
/// @param y
/// @param z
Vector2::Vector2(float x, float y)
	: x(x)
	, y(y)
{
}

//-------------------------------------------------------------------------------------------------
/// ベクトルの長さを返す
float Vector2::Magnitude() const
{
	return (float)sqrt(pow(x, 2.0) + pow(y, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// 長さを1に変換したベクトルを返す
Vector2 Vector2::Normalized() const
{
	float magnitude = Magnitude();
	return {
		x / magnitude,
		y / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
Vector2 Vector2::operator-() const
{
	return {
		-x,
		-y
	};
}
Vector2 Vector2::operator +(float aValue) const
{
	return {
		x + aValue,
		y + aValue
	};
}
Vector2 Vector2::operator -(float aValue) const
{
	return {
		x - aValue,
		y - aValue
	};
}
Vector2 Vector2::operator *(float aValue) const
{
	return {
		x * aValue,
		y * aValue
	};
}
Vector2 Vector2::operator /(float aValue) const
{
	return {
		x / aValue,
		y / aValue
	};
}
Vector2 Vector2::operator +(const Vector2& aVector) const
{
	return {
		x + aVector.x,
		y + aVector.y
	};
}
Vector2 Vector2::operator -(const Vector2& aVector) const
{
	return {
		x - aVector.x,
		y - aVector.y
	};
}
Vector2 Vector2::operator *(const Vector2& aVector) const
{
	return {
		x * aVector.x,
		y * aVector.y
	};
}
Vector2 Vector2::operator /(const Vector2& aVector) const
{
	return {
		x / aVector.x,
		y / aVector.y
	};
}

//-------------------------------------------------------------------------------------------------
bool Vector2::operator ==(const Vector2& aVector) const
{
	if (x != aVector.x) {
		return false;
	}
	if (y != aVector.y) {
		return false;
	}
	return true;
}
bool Vector2::operator !=(const Vector2& aVector) const
{
	if (x == aVector.x) {
		return false;
	}
	if (y == aVector.y) {
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
void Vector2::operator =(float aValue)
{
	x = aValue;
	y = aValue;
}
void Vector2::operator +=(float aValue)
{
	x += aValue;
	y += aValue;
}
void Vector2::operator -=(float aValue)
{
	x -= aValue;
	y -= aValue;
}
void Vector2::operator *=(float aValue)
{
	x *= aValue;
	y *= aValue;
}
void Vector2::operator /=(float aValue)
{
	x /= aValue;
	y /= aValue;
}
void Vector2::operator +=(const Vector2& aVector)
{
	x += aVector.x;
	y += aVector.y;
}
void Vector2::operator -=(const Vector2& aVector)
{
	x -= aVector.x;
	y -= aVector.y;
}
void Vector2::operator *=(const Vector2& aVector)
{
	x *= aVector.x;
	y *= aVector.y;
}
void Vector2::operator /=(const Vector2& aVector)
{
	x /= aVector.x;
	y /= aVector.y;
}

} // namespace
// EOF
