#pragma once

//-------------------------------------------------------------------------------------------------
#include <math.h>
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �O���錾
class Vector3;

/// 2D�x�N�g��
class Vector2
{
public:
    /// @name �R���X�g���N�^
    //@{
    Vector2();
    Vector2(float xy);
    Vector2(float x, float y);
    //@}

    //@ name �ϊ��֐�
    //@{
    /// �x�N�g���̒�����Ԃ�
    float Magnitude() const;
    /// �x�N�g����2��̒�����Ԃ�
    float SqrMagnitude() const;
    /// ������1�ɕϊ������x�N�g����Ԃ�
    Vector2 Normalized() const;
    //@}

    /// @ name ���Z�q�I�[�o�[���[�h
    //@{
    Vector2 operator -() const;
    Vector2 operator +(float aValue) const;
    Vector2 operator -(float aValue) const;
    Vector2 operator *(float aValue) const;
    Vector2 operator /(float aValue) const;
    Vector2 operator +(const Vector2& aVector) const;
    Vector2 operator -(const Vector2& aVector) const;

    bool operator ==(const Vector2& aVector) const;
    bool operator !=(const Vector2& aVector) const;

    void operator =(float aValue);
    void operator +=(float aValue);
    void operator -=(float aValue);
    void operator *=(float aValue);
    void operator /=(float aValue);
    void operator +=(const Vector2& aVector);
    void operator -=(const Vector2& aVector);
    void operator =(const Vector3& aVector);
    //@}

    /// @name �����o�ϐ�
    //@{
    float x;
    float y;
    //@}

    /// @name static const �����o�ϐ�
    //@{
    /// Vector2(0, 0)�Ɠ����Ӗ�
    const static Vector2 zero;
    /// Vector2(1, 1)�Ɠ����Ӗ�
    const static Vector2 one;
    /// Vector2(0, 1)�Ɠ����Ӗ�
    const static Vector2 up;
    /// Vector2(0, -1)�Ɠ����Ӗ�
    const static Vector2 down;
    /// Vector2(-1, 0)�Ɠ����Ӗ�
    const static Vector2 left;
    /// Vector2(1, 0)�Ɠ����Ӗ�
    const static Vector2 right;
    //@}

};

} // namespace
// EOF
