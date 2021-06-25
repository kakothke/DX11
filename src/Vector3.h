#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// �O���錾
class Vector2;

/// 3D�x�N�g��
class Vector3
{
public:
    /// @name �R���X�g���N�^
    //@{
    Vector3();
    Vector3(float xyz);
    Vector3(float x, float y, float z);
    //@}

    //@ name �ϊ��֐�
    //@{
    /// �x�N�g���̒�����Ԃ�
    float Magnitude() const;
    /// �x�N�g����2��̒�����Ԃ�
    float SqrMagnitude() const;
    /// ������1�ɕϊ������x�N�g����Ԃ�
    Vector3 Normalized() const;
    /// XMFLOAT4�^�ɕϊ����ĕԂ�
    DirectX::XMFLOAT4 XMFLOAT4() const;
    /// XMVECTOR�^�ɕϊ����ĕԂ�
    DirectX::XMVECTOR XMVECTOR() const;
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

    bool operator ==(const Vector3& aVector) const;
    bool operator !=(const Vector3& aVector) const;

    void operator =(float aValue);
    void operator +=(float aValue);
    void operator -=(float aValue);
    void operator *=(float aValue);
    void operator /=(float aValue);
    void operator +=(const Vector3& aVector);
    void operator -=(const Vector3& aVector);
    void operator =(const Vector2& aVector);
    //@}

    /// @name �����o�ϐ�
    //@{
    float x;
    float y;
    float z;
    //@}

    /// @name static const �����o�ϐ�
    //@{
    /// Vector3(0, 0, 0)�Ɠ����Ӗ�
    const static Vector3 zero;
    /// Vector3(1, 1, 1)�Ɠ����Ӗ�
    const static Vector3 one;
    /// Vector3(0, 1, 0)�Ɠ����Ӗ�
    const static Vector3 up;
    /// Vector3(0, -1, 0)�Ɠ����Ӗ�
    const static Vector3 down;
    /// Vector3(-1, 0, 0)�Ɠ����Ӗ�
    const static Vector3 left;
    /// Vector3(1, 0, 0)�Ɠ����Ӗ�
    const static Vector3 right;
    /// Vector3(0, 0, 1)�Ɠ����Ӗ�
    const static Vector3 forward;
    /// Vector3(0, 0, -1)�Ɠ����Ӗ�
    const static Vector3 back;
    //@}

};

} // namespace
// EOF
