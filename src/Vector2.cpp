#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// static const メンバ変数
const Vector2 Vector2::zero = Vector2(0, 0);
const Vector2 Vector2::one = Vector2(1, 1);
const Vector2 Vector2::up = Vector2(0, 1);
const Vector2 Vector2::down = Vector2(0, -1);
const Vector2 Vector2::left = Vector2(-1, 0);
const Vector2 Vector2::right = Vector2(1, 0);

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
/// @return ベクトルの長さ
float Vector2::Magnitude() const
{
	return (float)sqrt((x * x) + (y * y));
}

//-------------------------------------------------------------------------------------------------
/// ベクトルの2乗の長さを返す
/// @return ベクトルの2乗の長さ
float Vector2::SqrMagnitude() const
{
	return (x * x) + (y * y);
}

//-------------------------------------------------------------------------------------------------
/// 長さを1に変換したベクトルを返す
/// @return 長さを1に変換したベクトル
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

//-------------------------------------------------------------------------------------------------
bool Vector2::operator ==(const Vector2& aVector) const
{
	if (x == aVector.x && y == aVector.y) {
		return true;
	}
	return false;
}
bool Vector2::operator !=(const Vector2& aVector) const
{
	if (x != aVector.x || y != aVector.y) {
		return true;
	}
	return false;
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
void Vector2::operator =(const Vector3& aVector)
{
	x = aVector.x;
	y = aVector.y;
}
void Vector2::operator *=(const Quaternion& aQuaternion)
{
	*this = aQuaternion.operator*(*this);
}

} // namespace
// EOF
