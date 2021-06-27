#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// static const メンバ変数
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::back = Vector3(0.0f, 0.0f, -1.0f);

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
/// @return ベクトルの長さ
float Vector3::Magnitude() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

//-------------------------------------------------------------------------------------------------
/// ベクトルの2乗の長さを返す
/// @return ベクトルの2乗の長さ
float Vector3::SqrMagnitude() const
{
	return (x * x) + (y * y) + (z * z);
}

//-------------------------------------------------------------------------------------------------
/// 長さを1に変換したベクトルを返す
/// @return 長さを1に変換したベクトル
Vector3 Vector3::Normalized() const
{
	float magnitude = Magnitude();
	if (magnitude == 0) {
		magnitude = 1;
	}
	return {
		x / magnitude,
		y / magnitude,
		z / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT4型に変換して返す
/// @return XMFLOAT4
DirectX::XMFLOAT4 Vector3::XMFLOAT4() const
{
	return {
		x,
		y,
		z,
		1.0f
	};
}

//-------------------------------------------------------------------------------------------------
/// XMVECTOR型に変換して返す
/// @return XMVECTOR
DirectX::XMVECTOR Vector3::XMVECTOR() const
{
	return {
		x,
		y,
		z,
		1.0f
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

//-------------------------------------------------------------------------------------------------
bool Vector3::operator ==(const Vector3& aVector) const
{
	if (x == aVector.x && y == aVector.y && z == aVector.z) {
		return true;
	}
	return false;
}
bool Vector3::operator !=(const Vector3& aVector) const
{
	if (x != aVector.x || y != aVector.y || z != aVector.z) {
		return true;
	}
	return false;
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
void Vector3::operator =(const Vector2& aVector)
{
	x = aVector.x;
	y = aVector.y;
}
void Vector3::operator *=(const Quaternion& aQuaternion)
{
	*this = aQuaternion.operator*(*this);
}

} // namespace
// EOF
