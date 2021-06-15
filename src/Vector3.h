#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 3�����x�N�g��
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
    /// ������1�ɕϊ������x�N�g����Ԃ�
    Vector3 Normalized() const;
    /// XMFLOAT3�^�ɕϊ����ĕԂ�
    DirectX::XMFLOAT3 XMFLOAT3() const;
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
