#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 3次元ベクトル
class Vector3
{
public:
    /// @name コンストラクタ
    //@{
    Vector3();
    Vector3(float xyz);
    Vector3(float x, float y, float z);
    //@}

    //@ name 変換関数
    //@{
    /// ベクトルの長さを返す
    float Magnitude() const;
    /// 長さを1に変換したベクトルを返す
    Vector3 Normalized() const;
    /// XMFLOAT3型に変換して返す
    DirectX::XMFLOAT3 XMFLOAT3() const;
    /// XMVECTOR型に変換して返す
    DirectX::XMVECTOR XMVECTOR() const;
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
