#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 2次元ベクトル
class Vector2
{
public:
    /// @name コンストラクタ
    //@{
    Vector2();
    Vector2(float xy);
    Vector2(float x, float y);
    //@}

    //@ name 変換関数
    //@{
    /// ベクトルの長さを返す
    float Magnitude() const;
    /// 長さを1に変換したベクトルを返す
    Vector2 Normalized() const;
    //@}

    /// @ name 演算子オーバーロード
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

    /// @name メンバ変数
    //@{
    float x;
    float y;
    //@}

};

} // namespace
// EOF
