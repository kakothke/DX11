#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 2�����x�N�g��
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
    Vector2 operator *(const Vector2& aVector) const;
    Vector2 operator /(const Vector2& aVector) const;

    bool operator ==(const Vector2& aVector) const;
    bool operator !=(const Vector2& aVector) const;

    void operator =(float aValue);
    void operator +=(float aValue);
    void operator -=(float aValue);
    void operator *=(float aValue);
    void operator /=(float aValue);
    void operator +=(const Vector2& aVector);
    void operator -=(const Vector2& aVector);
    void operator *=(const Vector2& aVector);
    void operator /=(const Vector2& aVector);
    //@}

    /// @name �����o�ϐ�
    //@{
    float x;
    float y;
    //@}

};

} // namespace
// EOF
