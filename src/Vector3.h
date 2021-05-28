#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace DX11 {

/// 3次元ベクトル
class Vector3
{
public:
    /// @name コンストラクタ
    //@{
    Vector3();
    Vector3(float x, float y, float z);
    //@}

    /// @ name 演算子オーバーロード
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

    /// @name メンバ変数
    //@{
    float x;
    float y;
    float z;
    //@}

};

} // namespace
// EOF
