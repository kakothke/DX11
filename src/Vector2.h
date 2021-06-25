#pragma once

//-------------------------------------------------------------------------------------------------
#include <math.h>
#include "Vector3.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 前方宣言
class Vector3;

/// 2Dベクトル
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
    /// ベクトルの2乗の長さを返す
    float SqrMagnitude() const;
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

    /// @name メンバ変数
    //@{
    float x;
    float y;
    //@}

    /// @name static const メンバ変数
    //@{
    /// Vector2(0, 0)と同じ意味
    const static Vector2 zero;
    /// Vector2(1, 1)と同じ意味
    const static Vector2 one;
    /// Vector2(0, 1)と同じ意味
    const static Vector2 up;
    /// Vector2(0, -1)と同じ意味
    const static Vector2 down;
    /// Vector2(-1, 0)と同じ意味
    const static Vector2 left;
    /// Vector2(1, 0)と同じ意味
    const static Vector2 right;
    //@}

};

} // namespace
// EOF
