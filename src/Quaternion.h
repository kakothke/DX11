#pragma once

//-------------------------------------------------------------------------------------------------
#include <DirectXMath.h>
#include "Vector3.h"
#include "Vector2.h"

//-------------------------------------------------------------------------------------------------
namespace KDXK {

/// 前方宣言
class Vector3;
class Vector2;

/// クォータニオン
class Quaternion
{
public:
	/// @name コンストラクタ
	//@{
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(DirectX::XMVECTOR aQuaternion);
	//@}

	/// @name クォータニオン作成関数
	//@{
	/// Axisの周りをAngle度回転する回転を作成する
	static Quaternion AxisAngle(Vector3 aAxis, float aAngle);
	/// オイラー角で回転を作成する
	static Quaternion Euler(Vector3 aEulerAngle);
	//@}

	/// @name 変換関数
	//@{
	/// XMVECTORのメンバ変数を返す
	const DirectX::XMVECTOR& XMVECTOR() const;
	//@}

	/// @name 演算子オーバーロード
	//@{
	/// 逆クォータニオンを作成する
	Quaternion operator -() const;
	/// Vector3を回転させる
	Vector3 operator *(const Vector3& aVector) const;
	/// Vector2を回転させる
	Vector2 operator *(const Vector2& aVector) const;
	/// クォータニオン同士の乗算*
	Quaternion operator *(const Quaternion& aQuaternion) const;
	/// クォータニオン同士の乗算*=
	void operator *=(const Quaternion& aQuaternion);
	/// 等値演算子==
	bool operator ==(const Quaternion& aQuaternion) const;
	/// 等値演算子!=
	bool operator !=(const Quaternion& aQuaternion) const;
	//@}

private:
	/// @name プライベートメンバ変数
	//@{
	/// DirectXMathクォータニオン
	DirectX::XMVECTOR mQuaternion;
	//@}

};

} // namespace
// EOF
