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

using namespace DirectX;

/// �x�N�g���ϊ��v�Z
class Vector3Math
{
public:
    //@ name �ϊ��֐�
    //@{
    /// �x�N�g���̒�����Ԃ�
    static float Magnitude(Vector3 aVector);
    /// ������1�ɕϊ������x�N�g����Ԃ�
    static Vector3 Normalized(Vector3 aVector);
    /// XMFLOAT3�^�ɕϊ����ĕԂ�
    static const XMFLOAT3& XMFLOAT3(Vector3 aVector);
    //@}

private:
    Vector3Math();

};

} // namespace
// EOF
