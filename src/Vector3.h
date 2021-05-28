#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 3�����x�N�g��
class Vector3
{
public:
    /// @name �R���X�g���N�^
    //@{
    Vector3();
    Vector3(float x, float y, float z);
    //@}

    /// @ name ���Z�q�I�[�o�[���[�h
    //@{
    Vector3 operator -() const;
    Vector3 operator +(float aValue) const;
    Vector3 operator -(float aValue) const;
    Vector3 operator *(float aValue) const;
    Vector3 operator /(float aValue) const;
    Vector3 operator +(const Vector3& aVector) const;
    Vector3 operator -(const Vector3& aVector) const;
    Vector3 operator *(const Vector3& aVector) const;
    Vector3 operator /(const Vector3& aVector) const;

    bool operator ==(const Vector3& aVector) const;
    bool operator !=(const Vector3& aVector) const;

    void operator =(float aValue);
    void operator +=(float aValue);
    void operator -=(float aValue);
    void operator *=(float aValue);
    void operator /=(float aValue);
    void operator +=(const Vector3& aVector);
    void operator -=(const Vector3& aVector);
    void operator *=(const Vector3& aVector);
    void operator /=(const Vector3& aVector);
    //@}

    /// @name �����o�ϐ�
    //@{
    float x;
    float y;
    float z;
    //@}

};

} // namespace
// EOF
