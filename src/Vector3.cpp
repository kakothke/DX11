#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param xyz
Vector3::Vector3(float xyz)
	: x(xyz)
	, y(xyz)
	, z(xyz)
{
}

//-------------------------------------------------------------------------------------------------
/// コンストラクタ
/// @param x 
/// @param y
/// @param z
Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{
}

//-------------------------------------------------------------------------------------------------
/// ベクトルの長さを返す
float Vector3::Magnitude() const
{
	return (float)sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// 長さを1に変換したベクトルを返す
Vector3 Vector3::Normalized() const
{
	float magnitude = Magnitude();
	return {
		x / magnitude,
		y / magnitude,
		z / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT3型に変換して返す
DirectX::XMFLOAT3 Vector3::XMFLOAT3() const
{
	return {
		x,
		y,
		z
	};
}

//-------------------------------------------------------------------------------------------------
/// XMVECTOR型に変換して返す
DirectX::XMVECTOR Vector3::XMVECTOR() const
{
	return {
		x,
		y,
		z,
		0
	};
}

//-------------------------------------------------------------------------------------------------
Vector3 Vector3::operator-() const
{
	return {
		-x,
		-y,
		-z
	};
}
Vector3 Vector3::operator +(float aValue) const
{
	return {
		x + aValue,
		y + aValue,
		z + aValue
	};
}
Vector3 Vector3::operator -(float aValue) const
{
	return {
		x - aValue,
		y - aValue,
		z - aValue
	};
}
Vector3 Vector3::operator *(float aValue) const
{
	return {
		x * aValue,
		y * aValue,
		z * aValue
	};
}
Vector3 Vector3::operator /(float aValue) const
{
	return {
		x / aValue,
		y / aValue,
		z / aValue
	};
}
Vector3 Vector3::operator +(const Vector3& aVector) const
{
	return {
		x + aVector.x,
		y + aVector.y,
		z + aVector.z
	};
}
Vector3 Vector3::operator -(const Vector3& aVector) const
{
	return {
		x - aVector.x,
		y - aVector.y,
		z - aVector.z
	};
}
Vector3 Vector3::operator *(const Vector3& aVector) const
{
	return {
		x * aVector.x,
		y * aVector.y,
		z * aVector.z
	};
}
Vector3 Vector3::operator /(const Vector3& aVector) const
{
	return {
		x / aVector.x,
		y / aVector.y,
		z / aVector.z
	};
}

//-------------------------------------------------------------------------------------------------
bool Vector3::operator ==(const Vector3& aVector) const
{
	if (x != aVector.x) {
		return false;
	}
	if (y != aVector.y) {
		return false;
	}
	if (z != aVector.z) {
		return false;
	}
	return true;
}
bool Vector3::operator !=(const Vector3& aVector) const
{
	if (x == aVector.x) {
		return false;
	}
	if (y == aVector.y) {
		return false;
	}
	if (z == aVector.z) {
		return false;
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
void Vector3::operator =(float aValue)
{
	x = aValue;
	y = aValue;
	z = aValue;
}
void Vector3::operator +=(float aValue)
{
	x += aValue;
	y += aValue;
	z += aValue;
}
void Vector3::operator -=(float aValue)
{
	x -= aValue;
	y -= aValue;
	z -= aValue;
}
void Vector3::operator *=(float aValue)
{
	x *= aValue;
	y *= aValue;
	z *= aValue;
}
void Vector3::operator /=(float aValue)
{
	x /= aValue;
	y /= aValue;
	z /= aValue;
}
void Vector3::operator +=(const Vector3& aVector)
{
	x += aVector.x;
	y += aVector.y;
	z += aVector.z;
}
void Vector3::operator -=(const Vector3& aVector)
{
	x -= aVector.x;
	y -= aVector.y;
	z -= aVector.z;
}
void Vector3::operator *=(const Vector3& aVector)
{
	x *= aVector.x;
	y *= aVector.y;
	z *= aVector.z;
}
void Vector3::operator /=(const Vector3& aVector)
{
	x /= aVector.x;
	y /= aVector.y;
	z /= aVector.z;
}

} // namespace
// EOF
