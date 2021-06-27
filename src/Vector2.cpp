#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

//-------------------------------------------------------------------------------------------------
/// static const �����o�ϐ�
const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::down = Vector2(0.0f, -1.0f);
const Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::right = Vector2(1.0f, 0.0f);

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
Vector2::Vector2()
	: x(0)
	, y(0)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param xy
Vector2::Vector2(float xy)
	: x(xy)
	, y(xy)
{
}

//-------------------------------------------------------------------------------------------------
/// �R���X�g���N�^
/// @param x 
/// @param y
/// @param z
Vector2::Vector2(float x, float y)
	: x(x)
	, y(y)
{
}

//-------------------------------------------------------------------------------------------------
/// �x�N�g���̒�����Ԃ�
/// @return �x�N�g���̒���
float Vector2::Magnitude() const
{
	return sqrtf((x * x) + (y * y));
}

//-------------------------------------------------------------------------------------------------
/// �x�N�g����2��̒�����Ԃ�
/// @return �x�N�g����2��̒���
float Vector2::SqrMagnitude() const
{
	return (x * x) + (y * y);
}

//-------------------------------------------------------------------------------------------------
/// ������1�ɕϊ������x�N�g����Ԃ�
/// @return ������1�ɕϊ������x�N�g��
Vector2 Vector2::Normalized() const
{
	float magnitude = Magnitude();
	if (magnitude == 0) {
		magnitude = 1;
	}
	return {
		x / magnitude,
		y / magnitude
	};
}

//-------------------------------------------------------------------------------------------------
/// XMFLOAT4�^�ɕϊ����ĕԂ�
/// @return XMFLOAT4
DirectX::XMFLOAT4 Vector2::XMFLOAT4() const
{
	return {
		x,
		y,
		0.0f,
		1.0f
	};
}

//-------------------------------------------------------------------------------------------------
/// XMVECTOR�^�ɕϊ����ĕԂ�
/// @return XMVECTOR
DirectX::XMVECTOR Vector2::XMVECTOR() const
{
	return {
		x,
		y,
		0.0f,
		1.0f
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
