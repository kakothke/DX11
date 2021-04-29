#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
#include <math.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Vector3::Vector3()
	: x(0)
	, y(0)
	, z(0)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
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
/// �x�N�g���̒�����Ԃ�
float Vector3Math::Magnitude(Vector3 aVector)
{
	return (float)sqrt(pow(aVector.x, 2.0) + pow(aVector.y, 2.0) + pow(aVector.z, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// ������1�ɕϊ������x�N�g����Ԃ�
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
/// D3DXVECTOR3�^�ɕϊ����ĕԂ�
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
