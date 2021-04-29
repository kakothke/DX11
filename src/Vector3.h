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

using namespace DirectX;

/// ベクトル変換計算
class Vector3Math
{
public:
    //@ name 変換関数
    //@{
    /// ベクトルの長さを返す
    static float Magnitude(Vector3 aVector);
    /// 長さを1に変換したベクトルを返す
    static Vector3 Normalized(Vector3 aVector);
    /// XMFLOAT3型に変換して返す
    static const XMFLOAT3& XMFLOAT3(Vector3 aVector);
    //@}

private:
    Vector3Math();

};

} // namespace
// EOF
