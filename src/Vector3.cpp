#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// static const �����o�ϐ�
const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::back = Vector3(0.0f, 0.0f, -1.0f);

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
/// @return �x�N�g���̒���
float Vector3::Magnitude() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

//-------------------------------------------------------------------------------------------------
/// �x�N�g����2��̒�����Ԃ�
/// @return �x�N�g����2��̒���
float Vector3::SqrMagnitude() const
{
	return (x * x) + (y * y) + (z * z);
}

//-------------------------------------------------------------------------------------------------
/// ������1�ɕϊ������x�N�g����Ԃ�
/// @return ������1�ɕϊ������x�N�g��
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
/// XMFLOAT4�^�ɕϊ����ĕԂ�
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
/// XMVECTOR�^�ɕϊ����ĕԂ�
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
