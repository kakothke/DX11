#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

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
/// @param xyz
Vector3::Vector3(float xyz)
	: x(xyz)
	, y(xyz)
	, z(xyz)
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
/// �x�N�g���̒�����Ԃ�
float Vector3::Magnitude() const
{
	return (float)sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
}

//-------------------------------------------------------------------------------------------------
/// ������1�ɕϊ������x�N�g����Ԃ�
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
/// XMFLOAT3�^�ɕϊ����ĕԂ�
DirectX::XMFLOAT3 Vector3::XMFLOAT3() const
{
	return {
		x,
		y,
		z
	};
}

//-------------------------------------------------------------------------------------------------
/// XMVECTOR�^�ɕϊ����ĕԂ�
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
