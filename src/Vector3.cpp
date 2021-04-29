#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
#include <math.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

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

using namespace DirectX;

//-------------------------------------------------------------------------------------------------
/// ベクトルの長さを返す
float Vector3Math::Magnitude(Vector3 aVector)
{
	return (float)sqrt(pow(aVector.x, 2.0) + pow(aVector.y, 2.0) + pow(aVector.z, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// 長さを1に変換したベクトルを返す
Vector3 Vector3Math::Normalized(Vector3 aVector)
{
	float magnitude = Magnitude(aVector);
	return {
		aVector.x / magnitude,
		aVector.y / magnitude,
		aVector.z / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
/// D3DXVECTOR3型に変換して返す
const XMFLOAT3& Vector3Math::XMFLOAT3(Vector3 aVector)
{
	return {
		aVector.x,
		aVector.y,
		aVector.z
	};
}

} // namespace
// EOF
