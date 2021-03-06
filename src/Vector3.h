#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector2.h"
#include "Quaternion.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 前方宣言
class Vector2;
class Quaternion;

/// 3Dベクトル
class Vector3
{
public:
    /// @name コンストラクタ
    //@{
    Vector3();
    Vector3(float xyz);
    Vector3(float x, float y, float z);
    Vector3(const Vector2& aVector);
    //@}

    //@ name 変換関数
    //@{
    /// ベクトルの長さを返す
    float Magnitude() const;
    /// ベクトルの2乗の長さを返す
    float SqrMagnitude() const;
    /// 長さを1に変換したベクトルを返す
    Vector3 Normalized() const;
    /// XMFLOAT4型に変換して返す
    DirectX::XMFLOAT4 XMFLOAT4() const;
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
    void operator *=(const Quaternion& aQuaternion);
    //@}

    /// @name メンバ変数
    //@{
    float x;
    float y;
    float z;
    //@}

    /// @name static const メンバ変数
    //@{
    /// Vector3(0, 0, 0)と同じ意味
    const static Vector3 zero;
    /// Vector3(1, 1, 1)と同じ意味
    const static Vector3 one;
    /// Vector3(0, 1, 0)と同じ意味
    const static Vector3 up;
    /// Vector3(0, -1, 0)と同じ意味
    const static Vector3 down;
    /// Vector3(-1, 0, 0)と同じ意味
    const static Vector3 left;
    /// Vector3(1, 0, 0)と同じ意味
    const static Vector3 right;
    /// Vector3(0, 0, 1)と同じ意味
    const static Vector3 forward;
    /// Vector3(0, 0, -1)と同じ意味
    const static Vector3 back;
    //@}

};

} // namespace
// EOF
